��    M      �  g   �      �  9   �  -   �  ,   �  8     3   W  0   �  *   �  N   �  /   6  N   f     �  *   �  +    	     ,	  !   H	  +   j	  )   �	  #   �	  &   �	  -   
  !   9
  !   [
  +   }
  "   �
  (   �
     �
  S   
     ^     ~  #   �  #   �  #   �  #     #   ,  #   P  \   t  +   �  0   �      .  @   O  D   �  &   �  -   �     *  )   :  )   d  )   �  )   �  )   �  )     )   6  )   `     �  V   �  )   �  )   (  )   R  )   |  )   �  ,   �  )   �  )   '  )   Q  )   {  )   �  )   �  	   �  �        �  &   �  !   �  )     -   .     \     s  )   �  W  �  U   
  4   `  1   �  *   �  =   �  :   0  7   k  g   �  7     f   C  )   �  1   �  -        4  "   S  +   v  +   �  %   �  +   �  0      %   Q  %   w  .   �  &   �  .   �     "  ]   8  "   �      �  '   �  '     $   *  '   O  $   w  '   �  `   �  .   %  5   T  !   �  ]   �  P   
  (   [  /   �     �  .   �  '   �  )     )   E  )   o  )   �  5   �  3   �      -  b   N  )   �  )   �  1      1   7   0   i   4   �   0   �   2    !  :   3!  )   n!  )   �!  ,   �!     �!  �   �!     �"  5   �"  2   #  +   B#  5   n#     �#     �#  )   �#     &   ;         L         *          !   =          #       B                -   (   G   0   :          )   J          8       M   E           1   >   	       <   I             2   
      +   C           F                  6          ,            A             @   9                    K   /              3   .   ?       7          D   $          5   H   '      "       %   4        
If these values seem acceptable, use -f to force reset.
 
Report bugs to <pgsql-bugs@postgresql.org>.
   --help          show this help, then exit
   --version       output version information, then exit
   -O OFFSET       set next multitransaction offset
   -e XIDEPOCH     set next transaction ID epoch
   -f              force update to be done
   -l TLI,FILE,SEG force minimum WAL starting location for new transaction log
   -m XID          set next multitransaction ID
   -n              no update, just show extracted control values (for testing)
   -o OID          set next OID
   -x XID          set next transaction ID
 %s resets the PostgreSQL transaction log.

 %s: OID (-o) must not be 0
 %s: cannot be executed by "root"
 %s: could not change directory to "%s": %s
 %s: could not create pg_control file: %s
 %s: could not delete file "%s": %s
 %s: could not open directory "%s": %s
 %s: could not open file "%s" for reading: %s
 %s: could not open file "%s": %s
 %s: could not read file "%s": %s
 %s: could not read from directory "%s": %s
 %s: could not write file "%s": %s
 %s: could not write pg_control file: %s
 %s: fsync error: %s
 %s: internal error -- sizeof(ControlFileData) is too large ... fix PG_CONTROL_SIZE
 %s: invalid LC_COLLATE setting
 %s: invalid LC_CTYPE setting
 %s: invalid argument for option -O
 %s: invalid argument for option -e
 %s: invalid argument for option -l
 %s: invalid argument for option -m
 %s: invalid argument for option -o
 %s: invalid argument for option -x
 %s: lock file "%s" exists
Is a server running?  If not, delete the lock file and try again.
 %s: multitransaction ID (-m) must not be 0
 %s: multitransaction offset (-O) must not be -1
 %s: no data directory specified
 %s: pg_control exists but has invalid CRC; proceed with caution
 %s: pg_control exists but is broken or unknown version; ignoring it
 %s: transaction ID (-x) must not be 0
 %s: transaction ID epoch (-e) must not be -1
 64-bit integers Blocks per segment of large relation: %u
 Bytes per WAL segment:                %u
 Catalog version number:               %u
 Database block size:                  %u
 Database system identifier:           %s
 Date/time type storage:               %s
 First log file ID after reset:        %u
 First log file segment after reset:   %u
 Guessed pg_control values:

 If you are sure the data directory path is correct, execute
  touch %s
and try again.
 LC_COLLATE:                           %s
 LC_CTYPE:                             %s
 Latest checkpoint's NextMultiOffset:  %u
 Latest checkpoint's NextMultiXactId:  %u
 Latest checkpoint's NextOID:          %u
 Latest checkpoint's NextXID:          %u/%u
 Latest checkpoint's TimeLineID:       %u
 Maximum columns in an index:          %u
 Maximum data alignment:               %u
 Maximum length of identifiers:        %u
 Maximum length of locale name:        %u
 Maximum size of a TOAST chunk:        %u
 Options:
 The database server was not shut down cleanly.
Resetting the transaction log might cause data to be lost.
If you want to proceed anyway, use -f to force reset.
 Transaction log reset
 Try "%s --help" for more information.
 Usage:
  %s [OPTION]... DATADIR

 WAL block size:                       %u
 You must run %s as the PostgreSQL superuser.
 floating-point numbers pg_control values:

 pg_control version number:            %u
 Project-Id-Version: PostgreSQL 8.0
Report-Msgid-Bugs-To: 
POT-Creation-Date: 2009-01-16 09:17+0000
PO-Revision-Date: 2009-03-29 09:46+0400
Last-Translator: Serguei A. Mokhov <mokhov@cs.concordia.ca>
Language-Team: pgsql-rus <pgsql-rus@yahoogroups.com>
MIME-Version: 1.0
Content-Type: text/plain; charset=koi8-r
Content-Transfer-Encoding: 8bit
 
���� ��� �������� �������� �����������, ����������� -f ��� ���������������  ������.
 
��������� �� �������: <pgsql-bugs@postgresql.org>.
   --help          �������� ��� ��������� � �����
   --version       �������� ������ � �����
   -O OFFSET       ������ �������� ��������� ����������������
   -e XIDEPOCH     ������ �����/������� ���� ID ����������
   -f              �������������� ���������� ����������
   -l TLI,����,��� ��������� ����������� ��������� ��������� �������� WAL ��� ������ ������� ����������
   -m XID          ������ ID ��������� ����������������
   -n              ��� ����������, ������ �������� ����������� ����������� �������� (��� ������������)
   -o OID          ������ ����������� OID
   -x XID          ������ ID ��������� ����������
 %s ���������� ������ ���������� PostgreSQL.

 %s: OID (-o) �� ������ ���� 0
 %s: �� ����� ����������� "root"��
 %s: �� ������� ������� ���������� "%s": %s
 %s: �� ������� ������� ���� pg_control: %s
 %s: �� ������� ������� ���� "%s": %s
 %s: �� ������� ������� ���������� "%s": %s
 %s: �� ������� ������� ���� "%s" ��� ������: %s
 %s: �� ������� ������� ���� "%s": %s
 %s: �� ������� ������� ���� "%s": %s
 %s: �� ������� ������� �� ���������� "%s": %s
 %s: �� ������� �������� ���� "%s": %s
 %s: �� ������� �������� � ���� pg_control: %s
 %s: ������ fsync: %s
 %s: ���������� ������ -- sizeof(ControlFileData) ������� ����� ... ��������� PG_CONTROL_SIZE
 %s: ��������� �������� LC_COLLATE
 %s: ��������� �������� LC_CTYPE
 %s: ������������ �������� ��� ����� -O
 %s: ������������ �������� ��� ����� -e
 %s: ��������� �������� ��� ����� -l
 %s: ������������ �������� ��� ����� -m
 %s: ��������� �������� ��� ����� -o
 %s: ������������ �������� ��� ����� -x
 %s: ��������� lock-���� "%s"
������� �� ������? ���� ���, ������� ���� ���� � ���������� �����.
 %s: ID ���������������� (-m) �� ������ ���� 0
 %s: �������� ���������������� (-O) �� ������ ���� -1
 %s: �� ������� ���������� ������
 %s: pg_control ����������, �� ��� ����������� ����� CRC �������; ����������� � �������������
 %s: pg_control ����������, �� ������ģ� ��� ����������� ������; ������������...
 %s: ID ���������� (-x) �� ������ ���� 0
 %s: ����� ID ���������� (-e) �� ������ ���� -1
 64-������ ����� ������ �� ������� �������� ���������:      %u
 ���� �� ������� WAL:                %u
 ����� ������ ��������:                %u
 ������ ����� ����:                    %u
 ������������� ������� ��� ������:     %s
 ��� �������� ����/�������:            %s
 ������ ID ����� ������� ����� ������:             %u
 ������ ������� ����� ������� ����� ������:      %u
 ��������� �������� pg_control:

 ���� �� �������, ��� ���� � ���������� ������ ����������, ��������
  touch %s
� ���������� �����.
 LC_COLLATE:                           %s
 LC_CTYPE:                             %s
 NextMultiOffset ��������� ����������� �����:  %u
 NextMultiXactId ��������� ����������� �����:  %u
 NextOID ��������� ����������� �����:         %u
 NextXID ��������� ����������� �����:          %u/%u
 TimeLineID ��������� ����������� �����:      %u
 ������������ ����� ������� � �������:          %u
 ������������ ������ ������������ ������:               %u
 ������������ ����� ���������������:   %u
 ������������ ����� ����� ������:      %u
 ������������ ������ ������ TOAST:        %u
 �����:
 ������ ��� ������ �� ��� ��������� ����������.
����� ������� ���������� ����� �������� � ������ ������.
���� �� �ӣ �� ������ ���������� �� ������ �� ���, ����������� -f ��� ��������������� ������.
 ������ ���������� �������
 �������� "%s --help" ��� ����� ��������� ����������.
 �������������:
  %s [�����]... ����������-������

 ������ ����� WAL:                       %u
 �� ������ ��������� %s ��� ������������� PostgreSQL.
 ��������� ������� �������� pg_control:

 ����� ������ pg_control:              %u
 