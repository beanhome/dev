#ifndef FEVENT_H
#define FEVENT_H

#include "Utils.h"
#include "FDatation.h"

#include <libpq-fe.h>
#include "FLocation.h"
#include "FViewWindow.h"
#include "FListControl.h"

class FEventMap;

class FEvent
{
	private:
		FEvent();
		FEvent(uint id);
		FEvent(PGresult* res, int iTuple, bool bFull = false);
		FEvent(const FEvent& src);
		~FEvent();

	public:
		friend class FEventMap;

		uint						GetKey() const { return m_uId; }
		const string&				GetName() const { return m_sName; }
		const string&				GetDescription() const { return m_sDescription; }

		const uint					GetLocationCount() const { return m_aLocation.size(); }
		const vector<FLocation>&	GetLocation() const { return m_aLocation; }
		vector<FLocation>&			GetLocation() { return m_aLocation; }
		const FLocation&			GetLocation(uint i) const { assert(i<m_aLocation.size()); return m_aLocation[i]; }

		const FDatation&			GetDatation() const { return m_oDatation; }
		FDatation&					GetDatation() { return m_oDatation; }

		uint						GetParent() const { return m_uParent; }

		void 						SetName(const char* sName) { m_sName = sName; }
		void 						SetDescription(const char* sDescription) { m_sDescription = sDescription; }
		void 						SetDatation(const FDatation& oDatation) { m_oDatation = oDatation; }
		void						SetParent(uint id) { m_uParent = id; }
		void						SetParent(const string& str) { m_sParent = str; }
		void						AddLocation(const FLocation& oLocation);
		void						AddLocation(const char* str);

		bool						IsParentNull() const { return m_uParent == 0 && m_sParent.length() == 0; }
		string						GetParentIdString() const;

		//void 						SetRoles(const char* sRoles) { m_sRoles = sRoles; }
		//void 						SetTags(const char* sTags) { m_sTags = sTags; }

		void						ForceComplete() { m_bIncomplete = false; }
		bool						IsIncomplete() const { return m_bIncomplete; }

		string						GetRolesString() const;
		bool						IsRole(const string& sRole) const;
		void						ClearRoles();
		void						AddRoles(const string& sRole);
		uint						GetRolesCount() const { return m_aRoles.size(); }

		string						GetTagsString() const;
		bool						IsTagged(const string& sTag) const;
		void						ClearTags();
		void						AddTags(const string& sTag);
		void						RemTag(const string& sTag);
		uint						GetTagsCount() const { return m_aTags.size(); }

		void 						Save();
		void 						Load();
		void 						Load(PGresult* res, int iTuple, bool bExpress = false);

		void						PushTagToSelection(SelectCountTagMap& aTag);
		void						ApplyTagModif(const SelectMap& aTagControl);

		void						PushRoleToSelection(SelectCountTagMap& aTag);
		void						ApplyRoleModif(const SelectMap& aTagControl);

		void						PushLocationToSelection(SelectCountLocMap& aLoc);

	private:
		bool 						LoadMainInfo(PGresult* res, int iTuple);
		bool 						SaveMainInfo();
		bool 						LoadLocation();
		bool 						SaveLocation();
		bool 						LoadRoles();
		bool 						SaveRoles();
		bool 						LoadTags();
		bool 						SaveTags();

	private:
		uint						m_uId;
		string						m_sName;
		string						m_sDescription;
		FDatation					m_oDatation;
		
		vector<FLocation>			m_aLocation;

		typedef set<string> TagSet;
		TagSet						m_aTags;
		typedef set<string> RoleSet;
		RoleSet						m_aRoles;

		uint						m_uParent;
		string						m_sParent;

		bool						m_bIncomplete;
};

#endif