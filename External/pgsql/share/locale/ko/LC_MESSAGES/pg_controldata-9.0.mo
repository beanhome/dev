��    0      �  C         (  X   )  C   �  -   �  !   �           7  )   G  )   q  )   �  )   �  )   �  )     )   C  )   m  )   �  ,   �  )   �  )     )   B  ,   l  ,   �  )   �  )   �  )     )   D  )   n  ,   �  ,   �  ,   �  )   	  &   I	  �   p	  )   �	  �   &
    �
     �     
          *     >     P  )   ^  )   �  	   �     �     �     �  �  �  P   �  E     /   L  %   |  *   �     �  )   �  )     )   .  )   X  )   �  )   �  )   �  "      "   #  ,   F  )   s  )   �  )   �  ,   �  ,     )   K  (   u  )   �  )   �  "   �  ,     ,   B  '   o  )   �     �  }   �  )   _  �   �  �   E     -     4     9     B     O  
   c  )   n  )   �     �     �     �     �     $   0              
                           !   ,      )   *   (   "             .   /   	   '                                      #   +   -   %                                          &                                              
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
POT-Creation-Date: 2010-09-09 16:34+0000
PO-Revision-Date: 2010-09-24 12:36-0400
Last-Translator: EnterpriseDB translation team <dev-escalations@enterprisedb.com>
Language-Team: EnterpriseDB translation team <dev-escalations@enterprisedb.com>
MIME-Version: 1.0
Content-Type: text/plain; charset=euc-kr
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=1; plural=0;
 
DATADIR�� ������ ���͸��� �������� ������, PGDATA ȯ�� ��������
����մϴ�.

 %s ���α׷��� PostgreSQL �����ͺ��̽� Ŭ�������� ���������� ������.

 %s: "%s" ������ �б� ���� �� �� �����ϴ�: %s
 %s: "%s" ������ ���� �� �����ϴ�: %s
 %s: ������ ���͸��� �������� �ʾҽ��ϴ�
 64-��Ʈ ���� ���� �����̼��� ���׸�Ʈ�� ���� ����: %u
 WAL ���׸�Ʈ�� ũ��(byte):            %u
 īŻ�α� ���� ��ȣ:                   %u
 �����ͺ��̽� ���� ũ��:               %u
 �����ͺ��̽� Ŭ������ ����:           %s
 �����ͺ��̽� �ý��� �ĺ���:           %s
 ��¥/�ð��� �ڷ��� ������:          %s
 Float4 �μ� ����:              %s
 Float8 �μ� ����:              %s
 ������ üũ����Ʈ ��ġ:               %X/%X
 ������ üũ����Ʈ NextMultiOffset:    %u
 ������ üũ����Ʈ NextMultiXactId:    %u
 ������ üũ����Ʈ NextOID:            %u
 ������ üũ����Ʈ NextXID:            %u/%u
 ������ üũ����Ʈ REDO ��ġ:          %X/%X
 ������ üũ����Ʈ TimeLineID:         %u
 �ε������� ����ϴ� �ִ� �� ��:      %u
 �ִ� �ڷ� ����:                       %u
 �ĺ��� �ִ� ����:                     %u
 TOAST ûũ�� �ִ� ũ��:        %u
 �ּ� ���� ������ ��ġ:                %X/%X
 ���� üũ����Ʈ ��ġ:                 %X/%X
 ��������: <pgsql-bugs@postgresql.org>.
 ������ üũ����Ʈ �ð�:               %s
 ���� �ڼ��� ������ "%s --help"
 ����:
  %s [�ɼ�] [DATADIR]

�ɼǵ�:
  --help         �� ������ �����ְ� ��ħ
  --version      ���� ������ �����ְ� ��ħ
 WAL ���� ũ��:                        %u
 ���: ���� CRC üũ������ ���Ͽ� �ִ� ���� Ʋ���ϴ�.
�� ���� ������ �ջ�Ǿ��ų�, �� ���α׷��� ��Ʈ�� ������ ������ Ʋ��
����Դϴ�. ��������� ���� ���� ������ ��µ� �� �ֽ��ϴ�.

 ���: ����Ʈ ������ ��ġ���� �ʽ��ϴ�.
pg_control ������ �����ϴ� �� ���� ����Ʈ ������ 
�� ���α׷����� ����ϴ� ������ ��ġ�ؾ� �մϴ�.  �� ��� �Ʒ� ����� �ùٸ��� ������
�� ������ ���͸��� PostgreSQL�� ��ġ�� �� �����ϴ�.
 ������ ���� �ε��Ҽ� �ڷ� ���� �� ������ ���� ���� �� ���󰡵��� pg_control ������ ����ð�:           %s
 pg_control ���� ��ȣ:                 %u
 ������ ���� �� ���� �� �˼� ���� ���� �ڵ� 