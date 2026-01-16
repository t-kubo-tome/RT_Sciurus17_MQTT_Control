# RT_Sciurus17_MQTT_Control マニュアル

MetaworkMQTTプロトコルでの、RT Sciurus17の実機側の制御プログラムの使い方を説明する。

制御プログラムの開発環境での実行を前提とする。

公式ページは、[Sciurus17 研究用上半身人型ロボット _ 株式会社ア－ルティ](https://rt-net.jp/products/sciurus17/)である。

## クイックスタート

**1 ロボットの起動**

- 公式ページ中の「Sciurus17 入門ガイド」の「7 動作」に従って電源をONにする。長時間制御を行うため、「7.3 通信確認手順」にあるように通信タイムアウトを無効にしてメインスイッチをONにする
- 緊急停止ボタンがOFFである（上に引いてある）ことを確認する。また、ロボット制御時に、緊急停止したい場合は緊急停止ボタンをONにする（押す）ことを確認しておく

**2 PCでのプログラム実行**

- 開発環境では、Sciurus17に内蔵されているPCを使用する。PCの詳細は「Sciurus17 入門ガイド」の「Sciurus17 基本操作説明書（ROS編）」にある。プログラムはGUIを使用するため、PCにディスプレイを接続して使用するか、WiFi経由でリモートデスクトップ接続で使用する。
- 開発環境では、プログラムは`/home/sciurus/RT_Sciurus17_MQTT_Control`にあり、その場所の仮想環境（`.venv`）にインストールされている。インストールの方法は[インストール](#インストール)参照
- 開発環境では、ロボット制御コードは以下のコマンドで実行できる

まず仮想環境を有効にする。

```sh
source .venv/bin/activate
```

その状態でロボット制御コードを実行する。

```sh
python src/main.py
```

以下のようなGUI画面が起動する。

![](assets/manual/gui.png)

ロボット制御側で、MQTTでの制御を受け付けるようにするためには、以下の手順で操作を行う。

1. `ConnectRobot`でロボットに接続
2. `ConnectMQTT`でMQTTサーバーに接続
3. `EnableRobot`でロボットの状態に応じて電源ONやロボットコントローラの制御プログラム起動などを行う。すべて成功すれば`Enabled`のランプが緑色に点灯する
4. `StartMQTTControl`でMQTTでの制御を受け付けるようにする。成功すれば`MQTTControl`のランプが緑色に点灯する

`TidyPose`でロボットの先端がロボットの台の中央付近になる。`ChangeLogFile`でログ出力ディレクトリを現在の時刻の`log/<YY-mm-dd>/<HH-MM-SS>`に切り替えることができる。`DisableRobot`でモーターをOFFにできる。閉じるボタンでロボット制御コードを終了できる。

**3 ロボットの終了**

- 通常はロボットのみメインスイッチでOFFにしている。内蔵PCもOFFにする場合は、内蔵PCの電源ボタンをOFFにする。

## インストール

開発環境では、プログラムは`/home/sciurus/RT_Sciurus17_MQTT_Control`にインストール済みだが、ここではプログラムをインストールする方法を説明する。

まず、`rt_manipulators_cpp`をインストールする。

`https://github.com/rt-net/rt_manipulators_cpp`の`README.md`に従ってインストールする。

次に、プログラムのレポジトリからクローンする:

```sh
git clone https://github.com/t-kubo-tome/RT_Sciurus17_MQTT_Control.git
```

レポジトリのパス、ブランチは変更される可能性あり。

次に、Pythonの仮想環境を作成し、起動しておく。

```sh
python -m venv .venv
source .venv/bin/activate
```

次に、必要なライブラリをインストールする:

```sh
pip install -r src/requirements.txt
```

次に、`RT_Sciurus17_MQTT_Control`をビルド・インストールする:

```sh
./build.sh
```

環境変数は、`src/sciurus/.env.example`の変数を適宜書き換え、`src/sciurus/.env`に変更することで有効になる。

リアルタイムスケジューラを利用するための設定を行う。コマンド`python`のシンボリックリンクをたどった最終的なバイナリに対して、リアルタイムスケジューラを利用するための権限を付与する。例えば、バイナリが`/usr/bin/python3.10`の場合は、

```sh
sudo setcap cap_sys_nice=eip /usr/bin/python3.10
```

とする。但し、システムのバイナリに権限が付与される場合は、本システム以外にも影響を与える可能性があることに注意する必要がある。

`setcap`による設定をしない場合、毎回`sudo`を付けてコマンドを実行することで一時的にバイナリ（`python`）にリアルタイムスケジューラを利用するための権限を付与することができる。

```sh
sudo python src/main.py
```

特に仮想環境の`python`を用いる場合は`python`を`$(which python)`に置き換える必要がある。
