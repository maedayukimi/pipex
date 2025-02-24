This is pipex project
今回のプロジェクトPipexではLinuxコマンドによく使われるパイプを再現する

流れとしては

argumentsが正しい引数か確認する。確認事項は
ac == 5であること
file1 file2がそれぞれR_OK,W_OKであること。
cmd1 cmd2がそれぞれX_OKであること。ここまでに不足があればエラー出力。


例えば
cat file1 | grep "hello" > file2
これはfile1をcatし、その中から"hello"の含まれている行を抽出し、その行をfile2に出力するというコマンド。
つまりこんな感じ。

catが実行可能か、file1がR_OKかaccessでチェック。OKなら子プロセスをforkで作成し、その中でexecve。
cat grepそれぞれの子プロセスを用意。
catのPATHを引き渡してfile1のPATHを参照し、実行。
cat >> file1 => file1の内容をstdout、それをdup2で入力に変更。
入力先をgrepへ。

./pipex file1 "cat" "grep hello" file2

これはfile1をcatしてその中のhelloが存在する行をgrepで検索し、それをfile2に出力するというコマンドと同じになる。
そもそもパイプがどのような挙動をするのか

パイプとは

パイプを用いることでLinuxコマンドの流れをより簡潔にすることができる。
例えば 
cat file1 | wc -l
これはfile1の中身をcatし、それをwc -lに流すことができる
いつもならばfile1の中身をcatしてそれを別ファイルに流すかコピーしたりして
それをwc -lしなければならないが、パイプを用いることでそれを通して一行で完結させることができるもの。

そもそもLinuxのコマンドはどのように動いているのか

Linuxでは標準入力 標準出力 エラー出力の三つのファイルディスクリプタ、つまりファイルの形が三つある。
それぞれ stdin stdout stderr と表記される
なので、
1 LinuxのTerminal上にキーボードを用いてStdinでCommandを打ち込む
2 CommandがStdoutでディスプレイ上にそれを表示する 
の流れ。

ここにパイプを追加すると
1 LinuxのTerminal上にキーボードを用いてStdinでCommand1 | Command2 を打ち込む
2 Command1のStdoutをCommand2にStdinで入力する
3 Command2が受け取ったCommand1のStdoutをCommand2の対象として実行
4 Command2がStdoutでディスプレイ上にそれを表示する
...という流れ

ここからはパイプの挙動に更に詳しい説明を付け加える。

Linuxのプロセス間ではパイプは実際には匿名ファイルとしてOSが管理する
例えば上記の cat file1 | wc -l は内部的に次のような流れになる

pipe()システムコールで無名パイプ、anonymous pipeを作成
fork()により新しい子プロセスを作成
親プロセス(cat file1)はパイプの書き込み端(fd[1])にデータを書き込む		ここでいう～端とはつまり
子プロセス(wc -l)はパイプの読み込み端(fd[0])からデータを受け取る		stdin stdoutのことである
exceve()によりcat wcのバイナリが実行される
catの出力がpipeを通じてwcにstdinとして引き渡される
つまり、Linuxのパイプは一時的なバッファとして働くようになっている

なぜ子プロセスと親プロセスに分ける必要があるのか？

パイプを使うには親と子の二つのプロセスが必要になる
そしてパイプとは二つのプロセス間通信の仕組みであり、dup2を使いデータの流れを再現
execveで親の出力を子の入力として扱う

親プロセスの流れ

pipe(fd) を作成 (fd[0]: 読み込み, fd[1]: 書き込み)
fork() を呼び出し、子プロセスを作成
親 (cat) → dup2(fd[1], STDOUT_FILENO) で stdout をパイプの書き込み端に接続
親: execve("/bin/cat", ["cat", "file1"], NULL)
子プロセス

子 (wc -l) → dup2(fd[0], STDIN_FILENO) で stdin をパイプの読み込み端に接続
子: execve("/usr/bin/wc", ["wc", "-l"], NULL)

結果として親プロセスの出力が子の入力に流れる

なぜdup2を使うのか？

dup2はファイルディスクリプタを置き換える関数。
例えば ./push_swap 2 1 3 > a.txt...  これはpush_swapプロジェクトで死ぬほど使った確認用のコマンド。
通常./push_swap 2 1 3の出力はディスプレイに表示される...つまりfd = 1, 標準出力だ
しかし、以下のような
int main(void)
{
	int	fd[2];
	
	pipe(fd);
	if (fork() == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		char *cmd[] = {"/usr/bin/wc", "-l", NULL};
		execve(cmd[0], cmd, NULL);
		exit(1);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		char *cmd[] = {"./push_swap", "2", "1", "3", NULL};
		execve(cmd[0], cmd, NULL);
		exit(1);
	}
}

フォークで子プロセスを作成、その中でwc -lを整える
dup dup2 の違いとは？

dupはファイルディスクリプタのコピーを作成できる、新しいfdはOS側が自動で指定する
dup2は特定のfdを指定して置き換える そのためdup2(fd, STDOUT_FILENO)のようにしてファイル番号を指定する必要がある

そもそもプロセスとは？

プロセスとは実行中のプログラムのこと。プログラム、例えば./push_swapを実行するとプロセスが作成される
プロセスの持つ特徴として	プロセスID、pidを持つ。getpid()で取得が可能、今回は使わない
				独立したメモリ空間を持つ、つまり他のプロセスとメモリを共有しない
				親プロセスが存在する。getppid()で取得が可能、これも今回は使わない
などがある。
そして今回のプロジェクトではパイプを再現、つまりプロセスをコード中で親と子に分け、パイプで繋げる必要がある
そのため、forkを用いてプロセスを分離する必要がある

なぜexecveはint型の返り値を持つのに単体で使うことが多いのか？

成功した際に元のプログラムは書き換えられるため、return 0に到達する前に終了してしまうから。
しかし、失敗した際は-1が返り値として渡されるため、perrorを用いてエラーハンドリングをする必要がある。
これはpipeも同様で、成功時は0を返すので、printfなどと同様、エラーチェックや、他に使用する意図がない場合単体で呼び出せる

open closeとは？

int fd;
fd = open("file1.txt", O_WRONLY);
write(fd, "Hello, World!\n", 14);
close(fd);...のように使う
openは引き渡したファイルのディスクリプタを取得する、そしてwriteにfdを引き渡し、入力。
使用が終わったらcloseでfdを閉じる必要がある。これはfd leakを防ぐため。
今までwriteは1を引き渡し出力として扱うことが多かったがこれでfdを取得して動的にファイルへの書き込みができる。

execveとは？

int	execve(const char *filepath, char **argv, char **envp);
ファイルパスを指定し、プログラムに渡す引数、最後に環境変数を引き渡す。
今回は環境変数はNULLでOK。NULLに到達すると、親プロセスの環境変数を引き継ぐため、入力の手間を省く
例えばls -lを実行したい場合は
execve("usr/bin/ls", ft_split("ls -l", ' '), NULL);
で実行できる、なぜsplitしているかというと必要なダブルポインタをその場で作成し引き渡すため。
事前に用意してあるchar**があるならそれを引き渡してもよい
なぜ"usr/bin/ls"が実行されるのか、なぜlsのPATHを引き渡すとlsが実行されるかの説明は以下に。

そもそもどうやってLINUXコマンドが実行されているのか？

例えばlsを実行すると現在のディレクトリ内のファイル、フォルダを列挙してくれる
この際、lsを実行するとシェルはPATHに列挙されたディレクトリを左から順に検索
俺のPATHは以下の通り、:で区切られるようになっている
PATH=/home/mawako/.local/bin
:/usr/local/sbin	:/usr/local/bin	:/usr/sbin	:/usr/bin	:/sbin	:/bin	:/usr/games
:/usr/local/games	:/usr/lib/wsl/lib	:/mnt/c/WINDOWS/system32	:/mnt/c/WINDOWS
:/mnt/c/WINDOWS/System32/Wbem	:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/
:/mnt/c/WINDOWS/System32/OpenSSH/	:/mnt/c/Program Files/dotnet/	:/mnt/c/Program Files/Git/cmd
:/mnt/c/Users/maeda/AppData/Local/Microsoft/WindowsApps	:/mnt/c/Users/maeda/AppData/Local/Programs/Microsoft VS Code/bin:/mnt/c/Users/maeda/.dotnet/tools
このなかからbin/lsを探し、見つかったら実行するという形
今回で言えば usr/bin /binの二つがあるが、左から検索しているため usr/binに引っ掛かる形になる

そもそもa.outって何？

a.outとは実行ファイル。Linuxでは実行ファイルはELFフォーマットで作成される。
ELFとはExecutable and Linkable Formatの略であり、実行可能、リンク可能の略である。
これはつまりカーネルによって実行が可能、つまりパスを検索し実行可能ということ。
また、cc -c file.cなどで作成される.oファイル、つまりリンクするためのライブラリのファイルも扱うことができるということ。
そもそも実はlsなどの基本コマンドもELFの一種であり、今回用いるexecveでは実行ファイルを第一引数として読み込むため
lsなども読み込める。

リダイレクトって何？

stdout, stdinの出力先を変更すること。例えば、
./push_swap > a.txt とすれば本来 ./push_swap内で結果がprintfされるようになっている。つまり、stdoutされる。
しかし、> を用いてリダイレクト、つまりstdoutされる内容をa.txtに変更すると、画面に表示されるはずだった
./push_swapの内容がa.txtに出力される。この操作をリダイレクトという。
そして、dup2ではこのリダイレクトの概念をモロに使う。例えば
dup2(fd, STDOUT_FILENO) この場合、stdoutをfdにリダイレクトする。これによりstdoutされるはずの内容がfdに出力される。
この場合、fdとSTDOUTが繋がっている状態なので、fdをcloseしてもstdoutがfdに接続されているのでcloseしてOK

バッファリングって何？

execveを使用するとそのプロセス上にあるコードが一部読み取られなくなってしまうことがある。
なぜかというとexecveが成功するとその実行ファイルは別のPATH上のものに移り変わるため。
そのため、execveよりも上側にコードを書いていたとしても、それがバッファリングで管理されている場合
プロセスが終了すると同時にバッファリングが解放されるため、実行されない。
バッファリングされている関数かどうかは主にstdio.h(バッファリングアリ) unistd(バッファリングなし)で覚えたり、

int	main()
{
	printf("Hello, world!");
	sleep(3);
	printf("\n");
}
のようにしてsleepを用いることで判別できる

unlinkの仕様

unlinkはファイルのデータではなくリンクを削除する。
そもそもファイルシステムではファイルのデータとファイル名、つまりリンクは別れて管理されている。
unlinkはリンクを削除するだけでデータを削除するわけではない。
ファイル名とはディレクトリエントリ、ファイルデータとはi nodeのこと。
unlinkを使用するとディレクトリエントリは削除されるがi node自身はまだ残っている。
ディレクトリ構造:
  /home/user/
    ├── testfile.txt  → [iノード: 1234] → "Hello World"

int fd = open("testfile.txt", O_RDONLY);

プロセス: 12345
  ├── ファイルディスクリプタ(fd) → [iノード: 1234] → "Hello World"
こうなると、fdを通じてi nodeは保持される
unlinkを用いてディレクトリエントリを削除しても、fdから通じている間は情報は消えない。
しかしcloseすることでカーネルが完全にデータを削除する。
mawako ~/42tokyo/pipex % .
.: not enough arguments
mawako ~/42tokyo/pipex % /
zsh: permission denied: /
mawako ~/42tokyo/pipex % aaaa
zsh: command not found: aaaa
mawako ~/42tokyo/pipex %
