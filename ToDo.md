# Todo
- [x] Scoreの引数をConstに
- [ ] 次フレームをセットするのはStandardFrameだけでは
- [ ] 同じ実装多そう。継承するか？
 
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