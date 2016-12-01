# Table related Groonga functions

### ```table_get_value``` 関数

テーブルとキーを指定し、指定のカラムの値に変換します

```
table_get_value(table_name, "output_column", key_value)
```

* table_name: 検索するテーブルを指定します。KEYをサポートするテーブルである必要があります。
* output_column: 入力したキーと一致した場合に出力するカラムを指定します。存在しない場合はnullが返ります
* key_value: 検索するテーブルのキーの値を指定します。

## Install

Install libgroonga-dev.

Build this function.

    % sh autogen.sh
    % ./configure
    % make
    % sudo make install

## Usage

Register `functions/table`:

    % groonga DB
    > register functions/table

Now, you can use table related functions

## License

Public domain. You can copy and modify this project freely.
