# Table related Groonga functions

### ```table_get_value``` 関数

テーブルとキーを指定し、指定のカラムの値に変換します

```
table_get_value(table_name, "output_column", key_value)
```

* table_name: 検索するテーブルを指定します。KEYをサポートするテーブルである必要があります。
* output_column: 入力したキーと一致した場合に出力するカラムを指定します。存在しない場合はnullが返ります
* key_value: 検索するテーブルのキーの値を指定します。

```bash
plugin_register functions/table
[[0,0.0,0.0],true]
table_create Synonyms TABLE_HASH_KEY ShortText
[[0,0.0,0.0],true]
column_create Synonyms name COLUMN_SCALAR ShortText
[[0,0.0,0.0],true]
load --table Synonyms
[
{"_key": "groonga", "name": "Search engine"}
]
[[0,0.0,0.0],1]
table_create Entries TABLE_NO_KEY
[[0,0.0,0.0],true]
column_create Entries title COLUMN_SCALAR ShortText
[[0,0.0,0.0],true]
load --table Entries
[
{"title": "groonga"}
]
[[0,0.0,0.0],1]
select Entries --output_columns 'table_get_value(Synonyms, "name", title)'
[[0,0.0,0.0],[[[1],[["table_get_value",null]],["Search engine"]]]]
```

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
    > plugin_register functions/table

Now, you can use table related functions

## License

Public domain. You can copy and modify this project freely.
