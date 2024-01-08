# ブランチ説明
| ブランチ名   | 説明                                           | 用途                                                         |
| ------------ | ---------------------------------------------- | ------------------------------------------------------------ |
| tdd_template | テスト駆動開発が始められる状態のサンプルコード | 本ブランチから分岐することで、練習を始められるようにしている |
| master       | 現時点で最新のサンプルコード                   | 参考用                                                       |

# 環境構築 (Windows)
## VSCodeでC言語開発
- ["C/C++ for Visual Studio Code"](https://code.visualstudio.com/docs/languages/cpp)
  - "Go to the MinGW tutorial"へ
- Make
  - 以下を参考にMakeとVSCodeのMakefile Tools拡張をインストール
  - [Windowsのmakeコマンドの設定方法](https://zenn.dev/genki86web/articles/6e61c167fbe926)
## 単体テスト環境(CppUTest)
- インストール
  - CppUTest
    - 以下を参考に実施。CMakeのインストールも必要になっている。
    - [【丁寧解説】CppUTestをWindowsにインストール【MinGW-w64版】](https://yukblog.net/cpputest-mingw-install/)
- テスト実行まで
  - [公式のマニュアル](https://cpputest.github.io/manual.html)
    - そのままでは動かないことがおおいので、こまごま直しながら作る
    - 経緯メモ
      - CppUTestはC++実装なのでg++を使う必要があった
      - includeパスがg++に渡されてなかったCPPFLAGS → CXXFLAGSに置き換えた
      - Make結果を見ると、-Lや-l等、ライブラリへのリンクができていないことに気付いた([参考サイト](https://avaler0604.hateblo.jp/entry/2019/01/28/235002))。LDFLAGSとLDLIBに分離して書いたら出力された
  - [setup Cpputest framework](https://matheusmbar.com/bugfree-robot/2019/03/19/set_cppputest_framework.html)
    - 参考にしかけたが止めた
    - Linux系環境を前提にしている感がある


# 環境構築 (Mac)
- VSCode
- C言語コンパイル環境(gcc/g++)
- Make
  - 実行時すでに入っていた
  - 気づいたら入っていた(gcc --version, g++ --version, make --version)
- CppUTest
  - Homebrew導入済み環境だった
  - brew install cpputest を実行
  - [参考記事](https://zenn.dev/tarotene/articles/d078024b732f3e#%E3%82%A4%E3%83%B3%E3%82%B9%E3%83%88%E3%83%BC%E3%83%AB%E3%81%8B%E3%82%89%E7%92%B0%E5%A2%83%E5%A4%89%E6%95%B0%E3%81%AE%E8%A8%AD%E5%AE%9A%E3%81%BE%E3%81%A7)
