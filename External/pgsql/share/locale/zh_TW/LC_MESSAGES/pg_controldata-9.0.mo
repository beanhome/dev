��    1      �  C   ,      8  X   9  C   �  -   �  !         &     G  )   W  )   �  )   �  )   �  )   �  )   )  )   S  )   }  )   �  ,   �  )   �  )   (  )   R  ,   |  ,   �  )   �  )      )   *  )   T  )   ~  )   �  ,   �  ,   �  ,   ,	  )   Y	  &   �	  �   �	  )   6
  �   `
    '     7     D     M     d     x     �  )   �  )   �  	   �     �            �  )  K   �  4   :  (   o     �     �     �  1   �  2     -   J  0   x  .   �  2   �  1        =     [  4   y  &   �  &   �  /   �  !   ,  4   N  /   �     �     �  1   �  2        L     i  4   �  .   �  1   �  '     �   G     �  �   �  �   �     �     �  	   �     �     �     �  /   �  -        9     @     M     Z     %   1               
                           "   -      *   +      #             /   0   	   (                    )                 $   ,   .   &                                          '                                !             
If no data directory (DATADIR) is specified, the environment variable PGDATA
is used.

 %s displays control information of a PostgreSQL database cluster.

 %s: could not open file "%s" for reading: %s
 %s: could not read file "%s": %s
 %s: no data directory specified
 64-bit integers Blocks per segment of large relation: %u
 Bytes per WAL segment:                %u
 Catalog version number:               %u
 Database block size:                  %u
 Database cluster state:               %s
 Database system identifier:           %s
 Date/time type storage:               %s
 Float4 argument passing:              %s
 Float8 argument passing:              %s
 Latest checkpoint location:           %X/%X
 Latest checkpoint's NextMultiOffset:  %u
 Latest checkpoint's NextMultiXactId:  %u
 Latest checkpoint's NextOID:          %u
 Latest checkpoint's NextXID:          %u/%u
 Latest checkpoint's REDO location:    %X/%X
 Latest checkpoint's TimeLineID:       %u
 Maximum columns in an index:          %u
 Maximum data alignment:               %u
 Maximum length of identifiers:        %u
 Maximum number of function arguments: %u
 Maximum size of a TOAST chunk:        %u
 Minimum recovery ending location:     %X/%X
 Prior checkpoint location:            %X/%X
 Report bugs to <pgsql-bugs@postgresql.org>.
 Time of latest checkpoint:            %s
 Try "%s --help" for more information.
 Usage:
  %s [OPTION] [DATADIR]

Options:
  --help         show this help, then exit
  --version      output version information, then exit
 WAL block size:                       %u
 WARNING: Calculated CRC checksum does not match value stored in file.
Either the file is corrupt, or it has a different layout than this program
is expecting.  The results below are untrustworthy.

 WARNING: possible byte ordering mismatch
The byte ordering used to store the pg_control file might not match the one
used by this program.  In that case the results below would be incorrect, and
the PostgreSQL installation would be incompatible with this data directory.
 by reference by value floating-point numbers in archive recovery in crash recovery in production pg_control last modified:             %s
 pg_control version number:            %u
 shut down shutting down starting up unrecognized status code Project-Id-Version: PostgreSQL 8.4
Report-Msgid-Bugs-To: pgsql-bugs@postgresql.org
POT-Creation-Date: 2010-09-09 16:27+0000
PO-Revision-Date: 2010-09-24 17:06-0400
Last-Translator: EnterpriseDB translation team <dev-escalations@enterprisedb.com>
Language-Team: EnterpriseDB translation team <dev-escalations@enterprisedb.com>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=1; plural=0;
 
如果沒有指定資料目錄(DATADIR)就會使用環境變數PGDATA。

 %s 顯示PostgreSQL資料庫cluster控制資訊。

 %s: 無法開啟檔案"%s"以讀取: %s
 %s: 無法讀取檔案"%s": %s
 %s: 沒有指定資料目錄
 64位元整數 large relation每個區段的區塊數:       %u
 每個WAL區段的位元組數:                %u
 catalog版本號碼:                      %u
 資料庫區塊大小:                       %u
 資料庫cluster狀態:                    %s
 資料庫系統識別名稱:                   %s
 日期/時間儲存類型:                    %s
 Float4 參數傳遞方式:%s
 Float8 參數傳遞方式:%s
 最新的檢查點位置:                     %X/%X
 最新檢查點的 NextMultiOffset:%u
 最新檢查點的 NextMultiXactId:%u
 最新的檢查點NextOID:                  %u
 最新檢查點的 NextXID:%u/%u
 最新的檢查點REDO位置:                 %X/%X
 最新的檢查點TimeLineID:               %u
 索引中資料行上限:%u
 資料對齊上限:%u
 識別字的最大長度:                     %u
 函式參數的最大個數:                   %u
 TOAST 區塊大小上限:%u
 復原結束位置下限:%X/%X
 前一個檢查點位置:                     %X/%X
 回報錯誤至<pgsql-bugs@postgresql.org>。
 最新的檢查點時間:                     %s
 執行"%s --help"顯示更多資訊。
 用法：
  %s [OPTION] [DATADIR]

選項：
  --help         顯示說明訊息然後結束
  --version      顯示版本資訊然後結束
 WAL 區塊大小:%u
 警告：計算出來的CRC校驗值與儲存在檔案中的值不符。
可能是檔案損壞，或是與程式所預期的結構不同，下列
的結果是不可信賴的。

 警告: 可能出現位元組排序方式不相符情況
用來儲存 pg_control 檔的位元組排序
可能與此程式使用的位元組排序不相符。如此下列結果會不正確，而且
PostgreSQL 安裝會與此資料目錄不相容。
 傳址 傳值 浮點數 封存復原中 損毀復原中 正在運作 pg_control最後修改時間:               %s
 pg_control版本號碼:                   %u
 關閉 正在關閉 正在啟動 無法識別的狀態碼 