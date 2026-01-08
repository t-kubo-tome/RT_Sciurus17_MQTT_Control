# RT_Sciurus17_MQTT_Control マニュアル

MetaworkMQTTプロトコルでの、RT Sciurus17の実機側の制御プログラムの使い方を説明する。

制御プログラムの開発環境での実行を前提とする。

## クイックスタート

**1 ロボットの起動**

**2 PCでのプログラム実行**

まず仮想環境を有効にする。

```sh
source .venv/bin/activate
```

その状態でロボット制御コードを実行する。

```sh
python src/main.py
```

## インストール

開発環境では、プログラムは/home/sciurus/RT_Sciurus17_MQTT_Controlにインストール済みだが、ここではプログラムをインストールする方法を説明する。

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
