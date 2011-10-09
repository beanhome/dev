#ifndef FQUERY_H
#define FQUERY_H

//////////////////////////////////////////////////////////////////////////

#define FQ_EVENT_BEGIN								\
"SELECT	DISTINCT 									\
  \"Event\".id,										\
  \"Event\".name,									\
  \"Event\".description,							\
  \"Event\".datation,								\
  \"Event\".parent,									\
  (\"Event\".datation).start as start				\
  FROM 												\
  \"Event\"	"								

//  TODO Join with auth event
#define FQ_EVENT_COND_NAMEREGEXP					\
	"\"Event\".name LIKE '%s' "

#define FQ_EVENT_COND_DATE_START					\
	"(\"Event\".datation).start > '%s' "

#define FQ_EVENT_COND_DATE_END						\
	"(\"Event\".datation).end < '%s' "

#define FQ_EVENT_COND_LAST_START					\
	"update_date > '%s' "

#define FQ_EVENT_COND_LAST_END						\
	"update_date < '%s' "

#define FQ_EVENT_COND_DATE_NULL						\
	"\"Event\".datation IS NULL "

#define FQ_EVENT_COND_PARENT						\
	"(\"Event\".parent = (SELECT id FROM \"Event\" WHERE name = '%s') OR \"Event\".id = (SELECT id FROM \"Event\" WHERE name = '%s')) "


//#define FQ_EVENT_COND_PARENT						\
//"\"Event\".parent = %d OR \"Event\".id = %d "

#define FQ_EVENT_END								\
  "ORDER BY	start ASC;"

//////////////////////////////////////////////////////////////////////////

#define FQ_EVENT_JOIN_LOCATION_BEGIN						\
  "INNER JOIN												\
   ( SELECT \"Event_Location\".event_id AS loc_id			\
     FROM \"Event_Location\" LEFT JOIN \"Location\"			\
     ON \"Event_Location\".location_id = \"Location\".id "


#define FQ_EVENT_JOIN_LOCATION_END							\
  "  ) AS loc												\
   ON \"Event\".id = loc.loc_id "

//////////////////////////////////////////////////////////////////////////

#define FQ_EVENT_JOIN_ROLE_BEGIN							\
	"INNER JOIN												\
( SELECT \"Event_Role\".event_id AS role_id					\
FROM \"Event_Role\" "

#define FQ_EVENT_JOIN_ROLE									\
	"pg_has_role('%s', \"Event_Role\".role, 'MEMBER') "

#define FQ_EVENT_JOIN_ROLE_EVYBDY							\
	"\"Event_Role\".role = 'everybody' "						\

#define FQ_EVENT_JOIN_ROLE_END								\
	") AS role													\
ON \"Event\".id = role.role_id "

//////////////////////////////////////////////////////////////////////////

#define FQ_EVENT_JOIN_TAG_BEGIN								\
"INNER JOIN													\
( SELECT \"Event_Tags\".event_id AS tag_id					\
  FROM \"Event_Tags\" LEFT JOIN \"Tags\"					\
  ON \"Event_Tags\".tag_id = \"Tags\".id "					\

#define FQ_EVENT_JOIN_TAG									\
"\"Tags\".tag = '%s' "

#define FQ_EVENT_JOIN_TAG_END								\
") AS tag													\
ON \"Event\".id = tag.tag_id "

//////////////////////////////////////////////////////////////////////////

#define FQ_LOCATION_OLD										\
"SELECT id, country, city, district, street, address		\
  FROM \"Location\"											\
  WHERE \"id\" IN %s;"

#define FQ_LOCATION											\
"SELECT \"Location\".id, \"Location\".country, \"Location\".city, \"Location\".district, \"Location\".street, \"Location\".address		\
  FROM \"Event_Location\" LEFT JOIN \"Location\"																						\
  ON \"Event_Location\".location_id = \"Location\".id																					\
  WHERE \"Event_Location\".event_id = %d;"

#define FQ_KNOWERS											\
"SELECT role FROM \"Event_Role\" WHERE event_id = %d;"

#define FQ_TAGS												\
"SELECT \"Event_Tags\".event_id, \"Tags\".tag				\
  FROM \"Event_Tags\"										\
  JOIN \"Tags\"												\
  ON \"Event_Tags\".tag_id = \"Tags\".id					\
  WHERE \"Event_Tags\".event_id = %d;"

#define  FQ_ALLUSERS										\
"SELECT usename FROM pg_user;"

#define  FQ_ALLGROUPS										\
"SELECT groname FROM pg_group;"

#define  FQ_ALLROLES										\
"SELECT rolname FROM pg_roles;"

#define  FQ_ALLROLES_EXCEPT_PG								\
"SELECT rolname FROM pg_roles WHERE rolname != 'postgres';"

#define  FQ_ALLTAGS										\
"SELECT tag FROM \"Tags\" ORDER BY tag;"

#define  FQ_LOGINGROUPS											\
"SELECT groname FROM pg_group									\
  WHERE pg_has_role('%s', groname, 'MEMBER');"


#define FQ_TOP_ROLES											\
"SELECT															\
  rolname AS role,												\
  (																\
  SELECT count(*) > 0											\
    FROM pg_auth_members										\
    WHERE pg_get_userbyid(member) = rolname						\
    AND pg_get_userbyid(roleid) = '%s'							\
  ) AS direct,													\
  pg_has_role(rolname, '%s', 'USAGE') AS indirect				\
  FROM pg_roles													\
  WHERE rolname != '%s';"


#define FQ_SUB_ROLES											\
"SELECT															\
  rolname AS role,												\
  (																\
  SELECT count(*) > 0											\
    FROM pg_auth_members										\
    WHERE pg_get_userbyid(member) = '%s'						\
    AND pg_get_userbyid(roleid) = rolname						\
  ) AS direct,													\
  pg_has_role('%s', rolname, 'USAGE') AS indirect				\
  FROM pg_roles													\
  WHERE rolname != '%s';"


#endif