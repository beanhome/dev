��    t      �  �   \      �	  ~   �	  -   P
  +   ~
  0   �
  7   �
  g        {  4   �  s   �  .   D  G   s  4   �  )   �  w     4   �     �  @   �  =     !   Y     {  ,   �  1   �  *   �  -   #  -   Q  1     '   �  &   �  +      "   ,      O     p  #   �     �  )   �  =   �  '   "  '   J  	   r     |  &   �  <   �  !   �  	     -   (  9   V  +   �  "   �     �  ,   �     '     F  *   e  '   �     �     �  !   �     	  !   "     D      Y  3   z  /   �  '   �  ,     /   3  *   c  T   �  '   �          &     B     T     k  -   �  ,   �  ,   �  5        C  )   _  ?   �  8   �  0     5   3     i  A   ~  L   �       6     '   R  #   z     �  (   �  4   �  )   	     3     P      i  $   �     �  "   �  ,   �          /  '   O     w     �  $   �  0   �       8   &     _     }  &   �      �  �  �  m   �  /     0   F  -   w  3   �  y   �     S   -   r   s   �   -   !  >   B!  3   �!  ,   �!  {   �!  0   ^"     �"  F   �"  ;   �"     )#     I#  ,   a#  4   �#  -   �#  0   �#  0   "$  4   S$  *   �$  )   �$  .   �$     %     &%     A%  !   Y%     {%  ,   �%  >   �%  &   �%  &   &  
   =&     H&  '   [&  =   �&  '   �&     �&  $   �&  7   '  /   N'     ~'     �'  $   �'     �'     �'  $   (     ((     F(     Z(  "   u(     �(  !   �(     �(     �(  ,   )  '   2)     Z)  !   y)  4   �)  -   �)  W   �)  !   V*     x*     �*     �*     �*     �*  %   �*  $   +  $   5+  4   Z+     �+     �+  -   �+  !   �+  $   ,  5   2,     h,  C   },  I   �,     -  '   -     C-     ^-     ~-  &   �-  +   �-  "   �-     .     .  '   0.  *   X.     �.  (   �.  *   �.     �.     	/  $   (/     M/     i/  +   �/  '   �/     �/  )   �/     0     20  $   H0     m0         >   o       :   Q   ,   V          M                     d   `   \       8          $   e          	                    
                  t                  b   a   <   !       i   ]   h   r   3   7      N   _   g      ^   Z      @                 c   1   U   k   .      [               s          O   )   L   0   H   G   f      J   F          #   %   m   W          R   ;   -   Y       X   4       (           C               K   '      p   I       *             5   &       9   E   =   B   l   T   6       j   S   P   /       +   A       n   ?   "   D                    2             q    
If no output file is specified, the name is formed by adding .c to the
input file name, after stripping off .pgc if present.
 
Report bugs to <pgsql-bugs@postgresql.org>.
   --help         show this help, then exit
   --regression   run in regression testing mode
   --version      output version information, then exit
   -C MODE        set compatibility mode; MODE can be one of
                 "INFORMIX", "INFORMIX_SE"
   -D SYMBOL      define SYMBOL
   -I DIRECTORY   search DIRECTORY for include files
   -c             automatically generate C code from embedded SQL code;
                 this affects EXEC SQL TYPE
   -d             generate parser debug output
   -h             parse a header file, this option includes option "-c"
   -i             parse system include files as well
   -o OUTFILE     write result to OUTFILE
   -r OPTION      specify run-time behavior; OPTION can be:
                 "no_indicator", "prepare", "questionmarks"
   -t             turn on autocommit of transactions
 %s at or near "%s" %s is the PostgreSQL embedded SQL preprocessor for C programs.

 %s, the PostgreSQL embedded C preprocessor, version %d.%d.%d
 %s: could not open file "%s": %s
 %s: no input files specified
 %s: parser debug support (-d) not available
 AT option not allowed in CLOSE DATABASE statement AT option not allowed in CONNECT statement AT option not allowed in DEALLOCATE statement AT option not allowed in DISCONNECT statement AT option not allowed in SET CONNECTION statement AT option not allowed in TYPE statement AT option not allowed in VAR statement AT option not allowed in WHENEVER statement COPY FROM STDIN is not implemented COPY FROM STDOUT is not possible COPY TO STDIN is not possible CREATE TABLE AS cannot specify INTO ERROR:  EXEC SQL INCLUDE ... search starts here:
 Error: include path "%s/%s" is too long on line %d, skipping
 NEW used in query that is not in a rule OLD used in query that is not in a rule Options:
 SHOW ALL is not implemented Try "%s --help" for more information.
 Unix-domain sockets only work on "localhost" but not on "%s" Usage:
  %s [OPTION]... FILE...

 WARNING:  arrays of indicators are not allowed on input constraint declared INITIALLY DEFERRED must be DEFERRABLE could not open include file "%s" on line %d could not remove output file "%s"
 cursor "%s" does not exist cursor "%s" has been declared but not opened cursor "%s" is already defined descriptor "%s" does not exist descriptor header item "%d" does not exist descriptor item "%s" is not implemented end of search list
 expected "://", found "%s" expected "@" or "://", found "%s" expected "@", found "%s" expected "postgresql", found "%s" incomplete statement incorrectly formed variable "%s" indicator for array/pointer has to be array/pointer indicator for simple data type has to be simple indicator for struct has to be a struct indicator variable must have an integer type initializer not allowed in EXEC SQL VAR command initializer not allowed in type definition internal error: unreachable state; please report this to <pgsql-bugs@postgresql.org> interval specification not allowed here invalid bit string literal invalid connection type: %s invalid data type key_member is always 0 missing "EXEC SQL ENDIF;" missing identifier in EXEC SQL DEFINE command missing identifier in EXEC SQL IFDEF command missing identifier in EXEC SQL UNDEF command missing matching "EXEC SQL IFDEF" / "EXEC SQL IFNDEF" more than one EXEC SQL ELSE multidimensional arrays are not supported multidimensional arrays for simple data types are not supported multidimensional arrays for structures are not supported nested arrays are not supported (except strings) no longer supported LIMIT #,# syntax passed to server nullable is always 1 only data types numeric and decimal have precision/scale argument only protocols "tcp" and "unix" and database type "postgresql" are supported out of memory pointer to pointer is not supported for this data type pointers to varchar are not implemented subquery in FROM must have an alias syntax error syntax error in EXEC SQL INCLUDE command too many levels in nested structure/union definition too many nested EXEC SQL IFDEF conditions type "%s" is already defined unmatched EXEC SQL ENDIF unrecognized data type name "%s" unrecognized descriptor item code %d unrecognized token "%s" unrecognized variable type code %d unsupported feature will be passed to server unterminated /* comment unterminated bit string literal unterminated hexadecimal string literal unterminated quoted identifier unterminated quoted string using unsupported DESCRIBE statement variable "%s" is neither a structure nor a union variable "%s" is not a pointer variable "%s" is not a pointer to a structure or a union variable "%s" is not an array variable "%s" is not declared variable "%s" must have a numeric type zero-length delimited identifier Project-Id-Version: PostgreSQL 8.4
Report-Msgid-Bugs-To: pgsql-bugs@postgresql.org
POT-Creation-Date: 2010-09-09 16:34+0000
PO-Revision-Date: 2010-09-24 17:04-0400
Last-Translator: EnterpriseDB translation team <dev-escalations@enterprisedb.com>
Language-Team: EnterpriseDB translation team <dev-escalations@enterprisedb.com>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=1; plural=0;
 
如果未指定輸出檔，檔名就是將輸入檔的檔名
去掉 .pgc  (如果有的話) 再加上 .c。
 
回報錯誤給<pgsql-bugs@postgresql.org>。
   --help         顯示此說明，然後結束
   --regression   以迴歸測試模式執行
   --version      輸出版本資訊，然後結束
   -C 模式        設定相容性模式，模式可以是下列其中一項
                 "INFORMIX"、"INFORMIX_SE"
   -D 符號      定義符號
   -I 目錄   搜尋 Include 檔案的目錄
   -c             自動從內嵌 SQL 程式碼產生 C 程式碼，
                 EXEC SQL TYPE 會受到影響
   -d             產生解譯器偵錯輸出
   -h             解譯標頭檔，此選項包含選項 "-c"
   -i             同時解譯系統 Include 檔案
   -o 輸出檔     將結果寫入輸出檔
   -r 選項      指定執行階段行為，選項可以是:
                 "no_indicator"、"prepare"、"questionmarks"
   -t             開啟交易自動提交功能
 在"%s"附近發生 %s %s 是 PostgreSQL 內嵌 SQL 前置處理器，適用於 C 程式。

 %s，PostgreSQL 內嵌 C 前置處理器，版本 %d.%d.%d
 %s: 無法開啟檔案"%s": %s
 %s: 未指定輸入檔
 %s: 解譯器偵錯支援 (-d) 無法使用
 CLOSE DATABASE 陳述式中不允許使用 AT 選項 CONNECT 陳述式中不允許使用 AT 選項 DEALLOCATE 陳述式中不允許使用 AT 選項 DISCONNECT 陳述式中不允許使用 AT 選項 SET CONNECTION 陳述式中不允許使用 AT 選項 TYPE 陳述式中不允許使用 AT 選項 VAR 陳述式中不允許使用 AT 選項 WHENEVER 陳述式中不允許使用 AT 選項 未實作 COPY FROM STDIN COPY FROM STDOUT 不可行 COPY TO STDIN 不可行 CREATE TABLE AS 不能指定 INTO 錯誤: EXEC SQL INCLUDE ... 在此處開始搜尋:
 錯誤: Include 路徑 "%s/%s" 太長 (位於行 %d)，略過
 查詢中使用的 NEW 不在規則中 查詢中使用的 OLD 不在規則中 選項：
 未實作 SHOW ALL 執行"%s --help"顯示更多資訊。
 Unix-可用域通訊端僅適用 "localhost"，不適用 "%s" 使用方法:
%s [OPTION]...檔案...

 警告: 輸入中不允許使用指標陣列 限制宣告的 INITIALLY DEFERRED 必須是 DEFERRABLE 無法開啟 Include 檔案 "%s" (位於行 %d) 無法移除輸出檔 "%s"
 cursor "%s"不存在 指標 "%s" 已宣告但尚未開啟 指標 "%s" 已定義 描述子 "%s" 不存在 描述子標頭項目 "%d" 不存在 未實作描述子項目 "%s" 搜尋清單結尾
 預期 "://"，找到 "%s" 預期 "@" 或 "://"，找到 "%s" 預期 "@"，找到 "%s" 預期 "postgresql"，找到 "%s" 陳述式不完整 變數 "%s" 的格式不正確 陣列/指標的指標必須是陣列/指標 簡單資料型別的指標必須簡單 建構的指標必須是建構 指標變數必須是整數型別 EXEC SQL VAR 指令中不允許使用初始設定式 型別定義中不允許使用初始設定式 內部錯誤: 無法連線狀態，請回報此錯誤給 <pgsql-bugs@postgresql.org&gt; 這裡不允許使用間隔規格 位元字串實量無效 連線類型無效:%s 資料型別無效 key_member 一律為 0 遺漏 "EXEC SQL ENDIF;" EXEC SQL DEFINE 指令遺漏識別字 EXEC SQL IFDEF 指令遺漏識別字 EXEC SQL UNDEF 指令遺漏識別字 遺漏相符的 "EXEC SQL IFDEF" / "EXEC SQL IFNDEF" 多個 EXEC SQL ELSE 不支援多維度陣列 不支援簡單資料型別的多維度陣列 不支援多維度的結構陣列 不支援巢狀陣列 (字串除外) 不再支援的 LIMIT #,# 語法已傳遞到伺服器 Nullable 一律為 1 只有數值和十進位資料型別有精確度/小數位數參數 只支援通訊協定 "tcp" 和 "unix" 以及資料庫類型 "postgresql" 記憶體用盡 此資料型別不支援指標的指標 Varchar 的指標未實作 FROM中的子查詢要有別名 語法錯誤 EXEC SQL INCLUDE 指令的語法錯誤 巢狀結構/聯集定義中的層級過多 過多巢狀 EXEC SQL IFDEF 條件 型別 "%s" 已定義 EXEC SQL ENDIF 不相符  無法辨識的資料型別名稱 "%s" 無法辨識的描述子項目程式碼 %d 無法辨識的 token "%s" 無法辨識的變數型別程式碼 %d  不支援的功能將會傳遞到伺服器 未結束的 /* 註解 未結束的位元字串實量 未結束的十六進位字串實量 未結束的引號識別字 未結束的引號字串 正在使用不支援的 DESCRIBE 陳述式 變數 "%s" 不是結構也不是聯集 變數 "%s" 不是指標 變數 "%s"不是結構或聯集的指標 變數 "%s" 不是陣列 變數 "%s" 未宣告 變數 "%s" 必須具有數值型別 長度為零的分隔識別字 