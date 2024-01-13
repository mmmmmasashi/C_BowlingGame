# Todo
- [x] Scoreの引数をConstに
- [x] 最終フレームに対応
- [x] GameFactoryを作って生成処理を分離
- [ ] IGNORE対応
- [x] 次フレームをセットするのはStandardFrameだけでは。共通IFの仕事ではない。
- [ ] 同じ実装多そう。継承するか？
- [ ] ターキー対応(フレームをまたいで更に次へ)
 
# 気づきメモ
- ステップが大きくなりそうになったら仮実装を上手く使って、ステップを小さくする
  - 例)Spare(1,9,2,3)の時に、次のフレームからピン数を取る実装は面倒なので、ハードコードで2を返す。それ以外のスペアロジックだけにする
- 進め方
  - 最終フレーム以外の実装を、Frameとしてやりきる。
  - その後、interfaceを導入して、StandardFrameとLastFrameを、多態で実現する。
    - FrameにFrameInterfaceを導入
    - Frameは先頭に上記を持ち、内部ではＩＦを叩くだけ
    - StandardFrameを導入。Frameが持っていた処理をそちらへ移動
    - StandrdFrameの関数は、FrameInterfaceを介してコールバックされるだけなので、安心してStandardFrameとしてダウンキャストしてよい。