# Makefile : コメントは行頭にシャープ・コマンド部分でインデントしてコメントを書くとコメントまで実行されてしまう

# コンパイラを指定する・`$(CC)` で参照する・コマンド部分で `g++` を直接書いても問題はない
CC := g++

# `$ make` で実行されるのは最初に登場するターゲットになる
# `clean` というファイルが存在すると `$ make clean` が実行できなくなるので `.PHONY` を記述しておく
# `$(RM)` はデフォルトで `$ rm -f` コマンドが実行される
.PHONY: clean
clean:
	$(RM) ./practice-01 ./practice-02

# `ターゲット名: 依存するファイル` の順に書く・ファイルの更新日時を見てコマンドの再実行要否をチェックしている
practice-01: ./practice-01.cpp
	$(CC) ./practice-01.cpp -o ./practice-01

practice-02: ./practice-02.cpp
	$(CC) ./practice-02.cpp -o ./practice-02
