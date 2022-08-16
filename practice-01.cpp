#include <iostream>

// `gcc` ではなく `g++` でないとエラーになる
// `$ g++ ./practice-01.cpp -o ./practice-01 && ./practice-01` でビルド・実行
int main() {
  std::cout << "Hello World" << std::endl;  // 改行を入れつつストリームバッファをフラッシュする
}
