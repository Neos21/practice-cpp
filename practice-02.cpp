#include <cstdlib>   // system
#include <iostream>  // std::cout・std::cerr・std::endl
#include <string>    // std::string

// OS に応じて `start` や `open` や `xdg-open` コマンドを実行するラッパー
// 参考 : [cmdutils/google.cpp at master · rayalankenyon/cmdutils](https://github.com/rayalankenyon/cmdutils/blob/master/src/google.cpp)

// 慣例的には argc・argv : [C言語　main(int argc, char const *argv )について - Qiita](https://qiita.com/keitean/items/1a79c96adcf3fc02b1e5)
int main(int arg_count, char *arg_vector[]) {
  // 第1引数の必須チェック
  if(arg_count < 2) {
    std::cerr << "Please Input Argument. Aborted" << std::endl;  // `std::cerr` : 標準エラー出力
    return 1;
  }
  
  // - 定義済マクロによるコンパイラ・OS 判定 : `$ echo | gcc -dM -E -`
  //   - [C言語で定義済みマクロによるコンパイラ及びOS判定 新石器Wiki](https://www.yokoweb.net/dokuwiki/programing/c-language/compiler-os-macro-define)
  // - 条件コンパイルの `#ifdef` などは `#include` などのプリプロセッサのキーワードと同じくインデントせず行頭に書くのが慣例ではある
  std::string command_name =
    #ifdef _WIN32
      "start";  // Windows
    #elif __CYGWIN__
      "start";  // Windows GitBash
    #elif __APPLE__
      "open";  // MacOS
    #elif __linux__
      "xdg-open";  // Linux
    #else
      "__UNKNOWN_OS__";  // Other Unknown OS
    #endif
  
  if(command_name == "__UNKNOWN_OS__") {
    std::cerr << "Unknown OS. Aborted" << std::endl;
    return 1;
  }
  
  // コマンドを組み立てる
  std::string exec_command = command_name + " " + arg_vector[1];
  
  // 第2引数で `-o` を指定していたら実行するコマンドの文字列を出力する
  // - `==` ではなく `strcmp()` で比較しないと Warning が出る
  //   - [if(“文字列”==”文字列”)は文字列領域のアドレス比較で未規定動作(コンパイラ依存) - 怪しいC言語プログラムの直し方](https://bugs-c.info/gcc-wall-wextra/145/)
  if(arg_count >= 3 && strcmp(arg_vector[2], "-o") == 0) {
    std::cout << "$ " + exec_command << std::endl;
  }
  
  // コマンドを実行する
  system(exec_command.c_str());
  
  //#include <stdio.h>
  //printf("%s\n", command_name.c_str());
  // - `std::string` を `printf` するには `.c_str()` を使う
  //   - [文字列で学ぶC++入門 - Qiita](https://qiita.com/7shi/items/cac7b3e9b90bf91b00cc)
  
  // C++ における `main()` は `return` を書かなければ `0` になる
}

// 実行例 (MacOS)
// $ g++ ./practice-02.cpp -o ./practice-02 && ./practice-02 'https://example.com' -o
// $ open https://example.com
