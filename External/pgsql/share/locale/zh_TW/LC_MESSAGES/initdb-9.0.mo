��    �      <  �   \      (  R   )     |  
   �     �  -   �  �   �  �   n      A     5   X  J   �     �  6   �  P   ,  C   }  :   �  ]   �  4   Z  B   �  H   �  G     >   c  9   �  3   �  ?     /   P  -   �  E   �  y   �  (   n  #   �  7   �  (   �  ,     3   I  '   }  3   �  D   �  (     8   G  -   �  -   �  /   �  "     6   /  +   f     �  0   �  ;   �  $     /   ;     k  $   �  ~   �  1   -     _  /   }  J   �  �   �     �  C   �  -     8   E  !   ~  ,   �  /   �  4   �  A   2  @   t  ,   �  P   �  I   3  b   }     �     �  �     [   �     �     	     '  ;   ?  9   {  �   �  >   F  ;   �    �  u   �   q   H!  f   �!  s   !"  &   �"     �"     �"  &   �"  0   �"  .   +#  )   Z#  )   �#  "   �#  #   �#  "   �#      $  (   9$  "   b$     �$  "   �$  !   �$  ,   �$  $   %  *   7%  %   b%  !   �%     �%     �%     �%      �%     &     8&  -   S&  0   �&     �&     �&     �&  )   '     +'     /'  &   >'  %   e'     �'  +   �'  !   �'  �  �'  ?   �)     �)     *     *  /   #*  �   S*  �   �*  �   u+  >   n,  1   �,  D   �,      $-  ;   E-  A   �-  8   �-  :   �-  T   7.  5   �.  ;   �.  8   �.  8   7/  /   p/  5   �/  /   �/  6   0  +   =0  /   i0  6   �0  n   �0  !   ?1     a1  *   �1  !   �1  %   �1  !   �1  !   2  -   82  9   f2  /   �2  /   �2  ,    3  ,   -3  *   Z3  !   �3  8   �3  &   �3     4  '   4  ,   D4     q4  #   �4     �4  #   �4  h   �4  *   \5     �5  *   �5  F   �5  �   6     �6  /   �6  %   �6  1   7     ?7  (   ]7  "   �7  .   �7  :   �7  2   8  %   F8  J   l8  8   �8  Z   �8     K9     ^9  �   }9  O   :     S:      d:     �:  8   �:  ,   �:  �   ;  %   �;  -   �;  �   �;  Q   �<  e   =  Y   �=  ]   �=  '   :>     b>     s>  !   �>  '   �>  )   �>     �>     ?  &   2?     Y?     y?  !   �?      �?     �?     �?     @     ,@  $   I@     n@  4   �@     �@     �@     �@     	A     A     3A     QA     jA  ,   A  "   �A     �A     �A     B  $   #B     HB     PB  "   aB  !   �B     �B      �B     �B            X       m   C   U   e              q   Q   "       ^   ;   k       E   @   {   *       i          _           v          |   d      >   A   u      ?   +   o      t      h       J   �   c   [   Y   n   ]   1   a   P   W       b   D       j   �   !                         N           #   B   H      2   %   3   <          R   S   )   =   l   .             :              6      �   	   M              /       �   g      O              f               '       K   p      �      -   `   5   $   F   8              9   y   L   w   \       &       0       s             z   r       Z          
   G         V       I       ~              (   4       T          ,   }   x   7        
If the data directory is not specified, the environment variable PGDATA
is used.
 
Less commonly used options:
 
Options:
 
Other options:
 
Report bugs to <pgsql-bugs@postgresql.org>.
 
Success. You can now start the database server using:

    %s%s%spostgres%s -D %s%s%s
or
    %s%s%spg_ctl%s -D %s%s%s -l logfile start

 
WARNING: enabling "trust" authentication for local connections
You can change this by editing pg_hba.conf or using the -A option the
next time you run initdb.
       --lc-collate=, --lc-ctype=, --lc-messages=LOCALE
      --lc-monetary=, --lc-numeric=, --lc-time=LOCALE
                            set default locale in the respective category for
                            new databases (default taken from environment)
       --locale=LOCALE       set default locale for new databases
       --no-locale           equivalent to --locale=C
       --pwfile=FILE         read password for the new superuser from file
   %s [OPTION]... [DATADIR]
   -?, --help                show this help, then exit
   -A, --auth=METHOD         default authentication method for local connections
   -E, --encoding=ENCODING   set default encoding for new databases
   -L DIRECTORY              where to find the input files
   -T, --text-search-config=CFG
                            default text search configuration
   -U, --username=NAME       database superuser name
   -V, --version             output version information, then exit
   -W, --pwprompt            prompt for a password for the new superuser
   -X, --xlogdir=XLOGDIR     location for the transaction log directory
   -d, --debug               generate lots of debugging output
   -n, --noclean             do not clean up after errors
   -s, --show                show internal settings
  [-D, --pgdata=]DATADIR     location for this database cluster
 %s initializes a PostgreSQL database cluster.

 %s: "%s" is not a valid server encoding name
 %s: The password file was not generated. Please report this problem.
 %s: cannot be run as root
Please log in (using, e.g., "su") as the (unprivileged) user that will
own the server process.
 %s: could not access directory "%s": %s
 %s: could not access file "%s": %s
 %s: could not change permissions of directory "%s": %s
 %s: could not create directory "%s": %s
 %s: could not create symbolic link "%s": %s
 %s: could not determine valid short version string
 %s: could not execute command "%s": %s
 %s: could not find suitable encoding for locale %s
 %s: could not find suitable text search configuration for locale %s
 %s: could not get current user name: %s
 %s: could not obtain information about current user: %s
 %s: could not open file "%s" for reading: %s
 %s: could not open file "%s" for writing: %s
 %s: could not read password from file "%s": %s
 %s: could not write file "%s": %s
 %s: data directory "%s" not removed at user's request
 %s: directory "%s" exists but is not empty
 %s: encoding mismatch
 %s: failed to remove contents of data directory
 %s: failed to remove contents of transaction log directory
 %s: failed to remove data directory
 %s: failed to remove transaction log directory
 %s: file "%s" does not exist
 %s: file "%s" is not a regular file
 %s: input file "%s" does not belong to PostgreSQL %s
Check your installation or specify the correct path using the option -L.
 %s: input file location must be an absolute path
 %s: invalid locale name "%s"
 %s: locale %s requires unsupported encoding %s
 %s: must specify a password for the superuser to enable %s authentication
 %s: no data directory specified
You must identify the directory where the data for this database system
will reside.  Do this with either the invocation option -D or the
environment variable PGDATA.
 %s: out of memory
 %s: password prompt and password file cannot be specified together
 %s: removing contents of data directory "%s"
 %s: removing contents of transaction log directory "%s"
 %s: removing data directory "%s"
 %s: removing transaction log directory "%s"
 %s: symlinks are not supported on this platform %s: too many command-line arguments (first is "%s")
 %s: transaction log directory "%s" not removed at user's request
 %s: transaction log directory location must be an absolute path
 %s: unrecognized authentication method "%s"
 %s: warning: specified text search configuration "%s" might not match locale %s
 %s: warning: suitable text search configuration for locale %s is unknown
 Encoding %s is not allowed as a server-side encoding.
Rerun %s with a different locale selection.
 Enter it again:  Enter new superuser password:  If you want to create a new database system, either remove or empty
the directory "%s" or run %s
with an argument other than "%s".
 If you want to store the transaction log there, either
remove or empty the directory "%s".
 Passwords didn't match.
 Rerun %s with the -E option.
 Running in debug mode.
 Running in noclean mode.  Mistakes will not be cleaned up.
 The database cluster will be initialized with locale %s.
 The database cluster will be initialized with locales
  COLLATE:  %s
  CTYPE:    %s
  MESSAGES: %s
  MONETARY: %s
  NUMERIC:  %s
  TIME:     %s
 The default database encoding has accordingly been set to %s.
 The default text search configuration will be set to "%s".
 The encoding you selected (%s) and the encoding that the
selected locale uses (%s) do not match.  This would lead to
misbehavior in various character string processing functions.
Rerun %s and either do not specify an encoding explicitly,
or choose a matching combination.
 The files belonging to this database system will be owned by user "%s".
This user must also own the server process.

 The program "postgres" is needed by %s but was not found in the
same directory as "%s".
Check your installation.
 The program "postgres" was found by "%s"
but was not the same version as %s.
Check your installation.
 This might mean you have a corrupted installation or identified
the wrong directory with the invocation option -L.
 Try "%s --help" for more information.
 Usage:
 caught signal
 child process exited with exit code %d child process exited with unrecognized status %d child process was terminated by exception 0x%X child process was terminated by signal %d child process was terminated by signal %s copying template1 to postgres ...  copying template1 to template0 ...  could not change directory to "%s" could not find a "%s" to execute could not identify current directory: %s could not open directory "%s": %s
 could not read binary "%s" could not read directory "%s": %s
 could not read symbolic link "%s" could not remove file or directory "%s": %s
 could not set junction for "%s": %s
 could not stat file or directory "%s": %s
 could not write to child process: %s
 creating configuration files ...  creating conversions ...  creating dictionaries ...  creating directory %s ...  creating information schema ...  creating subdirectories ...  creating system views ...  creating template1 database in %s/base/1 ...  fixing permissions on existing directory %s ...  initializing dependencies ...  initializing pg_authid ...  invalid binary "%s" loading system objects' descriptions ...  ok
 out of memory
 selecting default max_connections ...  selecting default shared_buffers ...  setting password ...  setting privileges on built-in objects ...  vacuuming database template1 ...  Project-Id-Version: PostgreSQL 8.4
Report-Msgid-Bugs-To: pgsql-bugs@postgresql.org
POT-Creation-Date: 2010-09-09 16:27+0000
PO-Revision-Date: 2010-09-24 17:05-0400
Last-Translator: EnterpriseDB translation team <dev-escalations@enterprisedb.com>
Language-Team: EnterpriseDB translation team <dev-escalations@enterprisedb.com>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=1; plural=0;
 
如果沒有指定資料普錄就?使用環境變數PGDATA。
 
非常用選項:
 
選項：
 
其他選項:
 
回報錯誤給<pgsql-bugs@postgresql.org>。
 
執行成功。您現在可以使用下列指令啟動資料庫伺服器:

    %s%s%spostgres%s -D %s%s%s
或
    %s%s%spg_ctl%s -D %s%s%s -l logfile start

 
警告：對本地端連線使用"trust"驗證
你可以編輯pg_hba.conf改變設定，或在執行initdb時使用 -A 選項。
       --lc-collate=, --lc-ctype=, --lc-messages=LOCALE
      --lc-monetary=, --lc-numeric=, --lc-time=LOCALE
                            設定個別種類中的預設區域，for
                            新資料庫 (取自環境的預設值)
       --locale=LOCALE       設定新資料庫的預設區域
       --no-locale           功能同 --locale=C
       --pwfile=FILE         從檔案讀取新超級用戶的密碼
   %s [選項]... [資料目錄]
   -?, --help                顯示這份說明然後結束
   -A, --auth=METHOD         本地端預設的連線驗證方式
   -E, --encoding=ENCODING   新資料庫的預設編稼
   -L DIRECTORY              where to find the input files
   -T, --text-search-config=CFG
                            預設文本搜尋設定
   -U, --username=NAME       資料庫管理者名稱
   -V, --version             顯示版本資訊然後結束
   -W, --pwprompt            詢問新管理者的密碼
   -X, --xlogdir=XLOGDIR     交易日誌目錄的位置
   -d, --debug               顯示除錯訊息
   -n, --noclean             發生錯誤時不清除
   -s, --show                顯示內部設定
  [-D, --pgdata=]DATADIR     資料庫cluster的目錄
 %s 初始化PostgreSQL資料庫cluster。

 %s："%s" 不是有效的伺服器編碼名稱
 %s：無法產生密碼檔，請回報這個錯誤。
 %s：無法以root身份執行
請以將會擁有伺服器行程的非特權使用者登入(例如用"su")。
 %s：無法存取目錄"%s"：%s
 %s: 無法存取檔案 "%s":%s
 %s：無法修改目錄"%s"的權限：%s
 %s：無法建立目錄"%s"：%s
 %s: 無法建立符號連結 "%s":%s
 %s：無法取得短版本字串
 %s：無法執行命令"%s"：%s
 %s: 無法為區域 %s 找到合適的編碼
 %s: 無法為區域 %s 找到合適的文本搜尋設定
 %s：無法取得目前使用者的名稱：%s
 %s：無法取得目前使用者的資訊：%s
 %s：無法開啟檔案"%s"讀取資料: %s
 %s：無法開啟檔案"%s"寫入資料: %s
 %s：無法從檔案"%s"讀取密碼：%s
 %s：無法寫入檔案"%s"：%s
 %s：無法依使用者的要求刪除資料目錄 "%s"
 %s: 目錄 "%s" 存在但不是空的
 %s: 編碼不相符
 %s：無法刪除資料目錄的內容
 %s: 無法移除交易日誌目錄的內容
 %s：無法刪除資料目錄
 %s: 無法移除交易日誌目錄
 %s: 檔案 "%s" 不存在
 %s: 檔案 "%s" 不是一般檔案
 %s：輸入檔"%s"不屬於 PostgreSQL %s
請檢查你的安裝或用 -L 選項指定正確的路徑。
 %s：輸入檔位置必須是絕對路徑
 %s：無效的locale名稱"%s"
 %s: 區域 %s 需要不支援的編碼 %s
 %s：你必須提供管理者的密碼才能使用 %s 驗證方式。
 %s：未指定資料目錄
你必須指定資料庫系統存放資料的目錄，你可以使用 -D 選項
或是環境變數PGDATA。
 %s：記憶體用盡
 %s: 密碼提示和密碼檔不能一起指定
 %s：刪除資料目錄"%s"的內容
 %s: 正在移除交易日誌目錄的內容 "%s"
 %s：刪除資料目錄 "%s"
 %s: 正在移除交易日誌目錄 "%s"
 %s: 此平台不支援符號連結 %s：命令列參數過多(第一個是 "%s")
 %s: 無法依使用者要求刪除交易日誌目錄 "%s"
 %s: 交易日誌目錄位置必須是絕對路徑
 %s：無法辨認的驗證方式"%s"
 %s: 警告: 指定的文本搜尋設定 "%s" 可能與區域 %s 不相符
 %s: 警告: 適合區域 %s 的文本搜尋設定不明
 編碼 %s 不可做為伺服器端編碼。
請以不同的區域選項重新執行 %s。
 再輸入一次： 輸入新的管理者密碼： 如果你想建立新的資料庫系統，請將目錄 "%s" 移除或清空，
或是在執行 %s
 時加上 "%s" 以外的參數。
 如果您要將交易日誌儲存在那裡，
請移除或清空目錄 "%s"。
 密碼不符。
 用 -E 選項重新執行 %s。
 以除錯模式執行。
 以noclean模式執行，發生錯誤時不會清理。
 資料庫cluster會以locale %s初始化。
 資料庫cluster會以下列locale初始化
  COLLATE:  %s
  CTYPE:    %s
  MESSAGES: %s
  MONETARY: %s
  NUMERIC:  %s
  TIME:     %s
 預設資料庫編碼被設為 %s。
 預設的文本搜尋設定將設為 "%s"。
 您選取的編碼 (%s) 與
所選區域使用的編碼 (%s) 不相符。如此會導致
各種字元字串處理函式出現異常行為。
請重新執行 %s，且不以明確方式指定編碼，
或選擇相符的編碼組合。
 使用者"%s"將會成為資料庫系統檔案和伺服器行程的擁有者。

 %s 需要程式 "postgres"，但是在與"%s"相同的目錄中找不到。
請檢查你的安裝。
 "%s"已找到程式"postgres"，但是與 %s 的版本不符。
請檢查你的安裝。
 這可能表示你的安裝已損毀，或是指定
給引動選項 -L 的目錄不正確。
 執行"%s --help"取得更多資訊。
 使用方法：
 捕捉到信號
 子行程結束，結束代碼 %d 子行程結束，不明結束代碼 %d 子進程被例外(exception) 0x%X 終止 子行程被信號 %d 結束 子進程被信號 %s 終止 正在複製 template1 到 postgres... 複製template1到template0 ... 無法切換目錄至"%s" 未能找到一個 "%s" 來執行 無法識別目前的目錄：%s 無法開啟目錄 "%s":%s
 無法讀取二進制碼 "%s" 無法讀取目錄 "%s":%s
 無法讀取符號連結"%s" 無法移除檔案或目錄 "%s":%s
 無法為 "%s" 設定間隙:%s
 無法對檔案或目錄 "%s" 執行 stat 函式:%s
 無法寫至子行程：%s
 建立設定檔... 建立conversions ...  正在建立字典... 建立目錄 %s ... 建立information schema ...  正在建立子目錄... 建立系統views... 建立 template1 資料庫於 %s/base/1 ...  修正現有目錄 %s 的權限... 正在初始化相依性... 正在初始化 pg_authid... 無效的二進制碼 "%s" 正在載入系統物件的描述... 成功
 記憶體用盡
 選擇預設的max_connections ... 選擇預設的shared_buffers ... 設定密碼... 設定內建物件的權限 ...  重整資料庫template1 ... 