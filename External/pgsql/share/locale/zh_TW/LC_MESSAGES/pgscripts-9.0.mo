��    �      $  �   ,
      �  K   �     �  f     
   r  >   }  >   �  =   �  -   9  C   g  A   �     �  #        *  (   E     n  <   �  9   �  6     H   9  E   �  B   �  9     C   E  9   �  4   �  E   �  =   >  .   |  H   �  ;   �  E   0  :   v  5   �  7   �  9     7   Y  4   �  L   �  J     5   ^  2   �  7   �  2   �  2   2  J   e  :   �  5   �  G   !  0   i  <   �  0   �  M     J   V  G   �  4   �  H     E   g  9   �  v   �  <   ^  I   �  @   �  5   &  4   \  1   �  ;   �  5   �  6   5  3   l  4   �  =   �  8     8   L  8   �  2   �  9   �  6   +  9   b     �  /   �  <   �  #      #   9   ?   ]   %   �   #   �      �   3   !  &   ;!  5   b!  E   �!  I   �!  5   ("  I   ^"  5   �"  E   �"  F   $#  4   k#  D   �#     �#  *   $  8   .$  6   g$  %   �$  (   �$  (   �$  8   %  #   O%      s%     �%  8   �%  4   �%  $   "&     G&  ,   g&  ,   �&  ;   �&  9   �&     7'     L'     _'  *   }'  8   �'  ,   �'  8   (  #   G(  G   k(  4   �(  &   �(     )  )   ,)  7   V)     �)     �)  !   �)  +   �)     �)     *     ,*     I*     g*     l*  
   �*     �*     �*     �*  '   �*  "   +  2   *+  7   ]+  P   �+     �+  &   �+     ,     ,      ,     #,  :   2,     m,     o,  �  s,  8   8.     q.  u   �.  	   �.  '   /  @   )/  &   j/  /   �/  >   �/  <    0  !   =0  *   _0  #   �0  ,   �0     �0  A   �0  >   91  ;   x1  A   �1  >   �1  ;   52  8   q2  <   �2  <   �2  2   $3  >   W3  5   �3  /   �3  O   �3  5   L4  A   �4  5   �4  5   �4  8   05  E   i5  =   �5  :   �5  N   (6  N   w6  2   �6  /   �6  8   )7  8   b7  A   �7  F   �7  ;   $8  @   `8  C   �8  @   �8  G   &9  G   n9  D   �9  A   �9  >   =:  A   |:  K   �:  K   
;  9   V;  d   �;  >   �;  ;   4<  8   p<  8   �<  =   �<  :    =  8   [=  2   �=  8   �=  5    >  >   6>  C   u>  @   �>  H   �>  >   C?  8   �?  2   �?  /   �?  D   @     c@  *   o@  >   �@  '   �@  )   A  3   +A  5   _A  *   �A  #   �A  2   �A  %   B  9   =B  K   wB  A   �B  A   C  D   GC  D   �C  G   �C  D   D  3   ^D  ?   �D     �D  (   �D  9   E  0   UE  !   �E  %   �E  /   �E  /   �E     .F     KF     kF  /   �F  ,   �F     �F     G  '   "G  $   JG  ;   oG  9   �G     �G     �G  )   H  1   ;H  I   mH  .   �H  L   �H     3I  ;   SI  .   �I      �I     �I  #   �I  3   J     QJ     _J     vJ  #   �J     �J     �J  "   �J     K     %K     ,K  	   AK     KK     \K     xK  "   �K  %   �K  %   �K  ,   �K  M   !L     oL  *   L     �L     �L     �L     �L  3   �L     M     M        W   q   a   "   �   &      X      �   h       C   {          j   m   �   ^   :   ~       c               s   �       d   V          }   t      <       E   
   �       R   �   �   ,       *   e       K   �               D              O       S       g      	   _       9   N   �           J   2   �   �   \   f      >   k   w   ?              /         %                     0   �       -   �   !   1   .       �   )   �   F               `           �   8   v   �      H       @           I   �          �       �       Z       '          x   �       ]              (   A       l   G   Y   �   y   z           �   M   �              =   U   r   p       T      Q          �   $   �      P       |   B   i   4   +      ;   u       �   n   b               7   o       L   �   #               �               �   �   �      �   �       [   5       6   3       
By default, a database with the same name as the current user is created.
 
Connection options:
 
If one of -d, -D, -r, -R, -s, -S, and ROLENAME is not specified, you will
be prompted interactively.
 
Options:
 
Read the description of the SQL command CLUSTER for details.
 
Read the description of the SQL command REINDEX for details.
 
Read the description of the SQL command VACUUM for details.
 
Report bugs to <pgsql-bugs@postgresql.org>.
       --lc-collate=LOCALE      LC_COLLATE setting for the database
       --lc-ctype=LOCALE        LC_CTYPE setting for the database
   %s [OPTION]... DBNAME
   %s [OPTION]... LANGNAME [DBNAME]
   %s [OPTION]... [DBNAME]
   %s [OPTION]... [DBNAME] [DESCRIPTION]
   %s [OPTION]... [ROLENAME]
   --help                          show this help, then exit
   --help                       show this help, then exit
   --help                    show this help, then exit
   --version                       output version information, then exit
   --version                    output version information, then exit
   --version                 output version information, then exit
   -D, --no-createdb         role cannot create databases
   -D, --tablespace=TABLESPACE  default tablespace for the database
   -E, --encoding=ENCODING      encoding for the database
   -E, --encrypted           encrypt stored password
   -F, --freeze                    freeze row transaction information
   -I, --no-inherit          role does not inherit privileges
   -L, --no-login            role cannot login
   -L, --pglib=DIRECTORY     find language interpreter file in DIRECTORY
   -N, --unencrypted         do not encrypt stored password
   -O, --owner=OWNER            database user to own the new database
   -P, --pwprompt            assign a password to new role
   -R, --no-createrole       role cannot create roles
   -S, --no-superuser        role will not be superuser
   -T, --template=TEMPLATE      template database to copy
   -U, --username=USERNAME      user name to connect as
   -U, --username=USERNAME   user name to connect as
   -U, --username=USERNAME   user name to connect as (not the one to create)
   -U, --username=USERNAME   user name to connect as (not the one to drop)
   -W, --password               force password prompt
   -W, --password            force password prompt
   -a, --all                       vacuum all databases
   -a, --all                 cluster all databases
   -a, --all                 reindex all databases
   -c, --connection-limit=N  connection limit for role (default: no limit)
   -d, --createdb            role can create new databases
   -d, --dbname=DBNAME             database to vacuum
   -d, --dbname=DBNAME       database from which to remove the language
   -d, --dbname=DBNAME       database to cluster
   -d, --dbname=DBNAME       database to install language in
   -d, --dbname=DBNAME       database to reindex
   -e, --echo                      show the commands being sent to the server
   -e, --echo                   show the commands being sent to the server
   -e, --echo                show the commands being sent to the server
   -f, --full                      do full vacuuming
   -h, --host=HOSTNAME          database server host or socket directory
   -h, --host=HOSTNAME       database server host or socket directory
   -i, --index=INDEX         recreate specific index only
   -i, --inherit             role inherits privileges of roles it is a
                            member of (default)
   -i, --interactive         prompt before deleting anything
   -l, --list                show a list of currently installed languages
   -l, --locale=LOCALE          locale settings for the database
   -l, --login               role can login (default)
   -p, --port=PORT              database server port
   -p, --port=PORT           database server port
   -q, --quiet                     don't write any messages
   -q, --quiet               don't write any messages
   -r, --createrole          role can create new roles
   -s, --superuser           role will be superuser
   -s, --system              reindex system catalogs
   -t, --table='TABLE[(COLUMNS)]'  vacuum specific table only
   -t, --table=TABLE         cluster specific table only
   -t, --table=TABLE         reindex specific table only
   -v, --verbose                   write a lot of output
   -v, --verbose             write a lot of output
   -w, --no-password            never prompt for password
   -w, --no-password         never prompt for password
   -z, --analyze                   update optimizer hints
 %s (%s/%s)  %s cleans and analyzes a PostgreSQL database.

 %s clusters all previously clustered tables in a database.

 %s creates a PostgreSQL database.

 %s creates a new PostgreSQL role.

 %s installs a procedural language into a PostgreSQL database.

 %s reindexes a PostgreSQL database.

 %s removes a PostgreSQL database.

 %s removes a PostgreSQL role.

 %s removes a procedural language from a database.

 %s: "%s" is not a valid encoding name
 %s: cannot cluster a specific table in all databases
 %s: cannot cluster all databases and a specific one at the same time
 %s: cannot reindex a specific index and system catalogs at the same time
 %s: cannot reindex a specific index in all databases
 %s: cannot reindex a specific table and system catalogs at the same time
 %s: cannot reindex a specific table in all databases
 %s: cannot reindex all databases and a specific one at the same time
 %s: cannot reindex all databases and system catalogs at the same time
 %s: cannot vacuum a specific table in all databases
 %s: cannot vacuum all databases and a specific one at the same time
 %s: clustering database "%s"
 %s: clustering of database "%s" failed: %s %s: clustering of table "%s" in database "%s" failed: %s %s: comment creation failed (database was created): %s %s: could not connect to database %s
 %s: could not connect to database %s: %s %s: could not get current user name: %s
 %s: could not obtain information about current user: %s
 %s: creation of new role failed: %s %s: database creation failed: %s %s: database removal failed: %s %s: language "%s" is already installed in database "%s"
 %s: language "%s" is not installed in database "%s"
 %s: language installation failed: %s %s: language removal failed: %s %s: missing required argument database name
 %s: missing required argument language name
 %s: only one of --locale and --lc-collate can be specified
 %s: only one of --locale and --lc-ctype can be specified
 %s: query failed: %s %s: query was: %s
 %s: reindexing database "%s"
 %s: reindexing of database "%s" failed: %s %s: reindexing of index "%s" in database "%s" failed: %s %s: reindexing of system catalogs failed: %s %s: reindexing of table "%s" in database "%s" failed: %s %s: removal of role "%s" failed: %s %s: still %s functions declared in language "%s"; language not removed
 %s: too many command-line arguments (first is "%s")
 %s: user ID must be a positive number
 %s: vacuuming database "%s"
 %s: vacuuming of database "%s" failed: %s %s: vacuuming of table "%s" in database "%s" failed: %s Are you sure? Cancel request sent
 Could not send cancel request: %s Database "%s" will be permanently removed.
 Enter it again:  Enter name of role to add:  Enter name of role to drop:  Enter password for new role:  Name Password encryption failed.
 Password:  Passwords didn't match.
 Please answer "%s" or "%s".
 Procedural Languages Role "%s" will be permanently removed.
 Shall the new role be a superuser? Shall the new role be allowed to create databases? Shall the new role be allowed to create more new roles? Supported languages are plpgsql, pltcl, pltclu, plperl, plperlu, and plpythonu.
 Trusted? Try "%s --help" for more information.
 Usage:
 n no out of memory
 pg_strdup: cannot duplicate null pointer (internal error)
 y yes Project-Id-Version: PostgreSQL 8.4
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
預設會建立一個與使用者同名的資料庫。
 
連線選項:
 
如果 -d、-D、-r、-R、-s、-S 和 ROLENAME 其中一個未指定，系統會
以互動方式提示您輸入。
 
選項:
 
請參考SQL命令CLUSTER的說明。
 
請閱讀 SQL 指令 REINDEX 的描述以取得詳細資訊。
 
請參考SQL命令VACUUM的說明。
 
回報錯誤至<pgsql-bugs@postgresql.org>。
       --lc-collate=區域      資料庫的 LC_COLLATE 設定
       --lc-ctype=區域        資料庫的 LC_CTYPE 設定
   %s [選項]... 資料庫名稱
   %s [選項]... 語言 [資料庫名稱]
   %s [選項]... [資料庫名稱]
   %s [選項]... [資料庫名稱] [描述]
   %s [OPTION]...[ROLENAME]
   --help                          顯示這份說明然後結束
   --help                       顯示這份說明然後結束
   --help                    顯示這份說明然後結束
   --version                       顯示版本資訊然後結束
   --version                    顯示版本資訊然後結束
   --version                 顯示版本資訊然後結束
   -D, --no-createdb         角色無法建立資料庫
   -D, --tablespace=TABLESPACE  資料庫的預設tablespace
   -E, --encoding=編碼名稱      指定資料庫的編碼
   -E, --encrypted           加密儲存的密碼
   -F, --freeze                    凍結資料列交易資訊
   -I, --no-inherit          角色不會繼承權限
   -L, --no-login            角色不能登入
   -L, --pglib=目錄          在指定的目錄中尋找語言直譯器檔案
   -N, --unencrypted         不加密儲存的密碼
   -O, --owner=擁有者           指定新資料庫的擁有者
   -P, --pwprompt            指派密碼給新角色
   -R, --no-createrole       角色不能建立角色
   -S, --no-superuser        角色不會是超級用戶
   -T, --template=樣版名稱      指定要使用的資料庫樣板
   -U, --username=使用者名稱    用來連線的使用者
   -U, --username=使用者名稱 用來連線的使用者
   -U, --username=使用者名稱 用來連線的使用者(不是要建立的)
   -U, --username=使用者名稱 用來連線的使用者(不是要刪除的)
   -W, --password               強制密碼提示
   -W, --password            強制密碼提示
   -a, --all                       重整所有資料庫
   -a, --all                 重新排列所有資料庫
   -a, --all                 對所有資料庫進行索引重建
   -c, --connection-limit=N  角色的連線限制 (預設: 無限制)
   -d, --createdb            角色可以建立新資料庫
   -d, --dbname=資料庫名稱         重整指定的資料庫
   -d, --dbname=資料庫名稱   指定要刪除語言的資料庫
   -d, --dbname=資料庫名稱   重新排列指定的資料庫
   -d, --dbname=資料庫名稱       指定要安裝語言的資料庫
   -d, --dbname=資料庫名稱       要進行索引重建的資料庫
   -e, --echo                      顯示被送到伺服器的命令
   -e, --echo                   顯示被送到伺服器的命令
   -e, --echo                顯示被送到伺服器的命令
   -f, --full                      進行完整的資料庫重整
   -h, --host=主機名稱          資料庫伺服器主機或socket目錄
   -h, --host=主機名稱       資料庫伺服器的主機或socket目錄
   -i, --index=索引         只重新建立特定索引
   -i, --inherit             角色會繼承父角色的
                            權限 (預設)
   -i, --interactive         刪除任何東西前要先詢問
   -l, --list                顯示目前已安裝的語言
   -l, --locale=區域          資料庫的區域設定
   -l, --login               角色可以登入 (預設)
   -p, --port=埠號              資料庫伺服器的埠號
   -p, --port=埠號           資料庫伺服器的埠號
   -q, --quiet                     不顯示任何訊息
   -q, --quiet               不顯示任何訊息
   -r, --createrole          角色可以建立新角色
   -s, --superuser           角色會是超級用戶
   -s, --system              對系統目錄進行索引重建
   -t, --table='資料表名稱[(欄位)]' 重整指定的資料表
   -t, --table=資料表名稱    重新排列指定的資料表
   -t, --table=資料表         只對特定資料表進行索引重建
   -v, --verbose                   顯示詳細的執行訊息
   -v, --verbose             顯示詳細的執行訊息
   -w, --no-password            絕不提示密碼
   -w, --no-password         絕不提示密碼
   -z, --analyze                   更新效能調整器統計資料
 %s (%s/%s)  %s 清理並分析PostgreSQL資料庫。

 %s 重新排列所有資料庫中曾經重排的資料庫。

 %s 建立一個PostgreSQL資料庫。

 %s 會建立新的 PostgreSQL 角色。

 %s 安裝了程序語言至PostgreSQL資料庫。

 %s 會對 PostgreSQL 資料庫進行索引重建。

 %s 刪除了一個PostgreSQL資料庫。

 %s 會移除 PostgreSQL 角色。

 %s 刪除了一個資料庫中的程序語言。

 %s："%s"不是有效的編碼名稱
 %s：不能對所有資料庫指定重新排列資料表
 %s：不能同時重新排列所有資料庫和重新排列指定資料庫
 %s: 無法同時對特定索引和系統目錄進行索引重建
 %s: 無法對所有資料庫中的特定索引進行索引重建
 %s: 無法同時對特定資料表和系統目錄進行索引重建
 %s: 無法對所有資料庫中的特定資料表進行索引重建
 %s: 無法同時對所有資料庫和特定資料庫進行索引重建
 %s: 無法同時對所有資料庫和系統目錄進行索引重建
 %s：不能對所有資料庫指定重整資料表
 %s：不能同時重整所有資料庫和重整指定資料庫
 %s：重新排列資料庫"%s"
 %s：重新排列資料庫"%s"失敗: %s %s：重新排列資料表"%s"於資料庫"%s"失敗：%s %s：建立註解失敗(資料庫已建立)：%s %s：無法連線至資料庫 %s
 %s：無法連線至資料庫 %s：%s %s：無法取得目前使用者的名稱：%s
 %s：無法取得目前使用者的資訊：%s
 %s: 建立新角色失敗:%s %s：建立資料庫失敗：%s %s：刪除資料庫失敗：%s %s：語言"%s"已經被安裝至資料庫"%s"
 %s：語言"%s"未被安裝至資料庫"%s"
 %s：安裝語言失敗：%s %s：刪除語言失敗：%s %s：缺少必要參數資料庫名稱
 %s：缺少必要參數語言名稱
 %s: 只可以指定 --locale 和 --lc-collate 其中一個
 %s: 只可以指定 --locale 和 --lc-ctype 其中一個
 %s：查詢失敗：%s %s：查詢是：%s
 %s: 對資料庫 "%s" 進行索引重建
 %s: 對資料庫 "%s" 進行索引重建失敗:%s %s: 對索引 "%s" (位於資料庫 "%s" 中) 進行索引重建失敗:%s %s: 對系統目錄進行索引重建失敗:%s %s: 對資料表 "%s" (位於資料庫 "%s" 中) 進行索引重建失敗:%s %s: 移除角色 "%s" 失敗:%s %s：仍有 %s 個函式以語言"%s"宣告，不予刪除
 %s：命令列參數過多(第一個是 "%s")
 %s：使用者ID必須是正數
 %s：重整資料庫"%s"
 %s：重整資料庫"%s"失敗：%s %s：重整資料表"%s"於資料庫"%s"失敗：%s 您確定嗎? 取消要求已傳送
 無法傳送取消要求:%s 資料庫"%s"會被永久刪除。
 再輸入一次:  輸入要加入的角色名稱: 輸入要捨棄之角色的名稱: 輸入新角色的密碼: 名稱 密碼加密失敗.
 密碼： 密碼不符。
 請回應 "%s" 或 "%s"。
 程序語言 角色 "%s" 將會永久移除。
 新角色是否要成為超級用戶? 是否允許新角色建立資料庫? 是否允許新角色建立更多新角色 ? 支援的語言有plpgsql、pltcl、pltclu、plperl、plperlu和plpythonu。
 是否信任？ 執行"%s --help"以取得更多資訊。
 使用方法:
 n 否 記憶體用盡
 pg_strdup: 無法複製 Null 指標 (內部錯誤)
 y 是 