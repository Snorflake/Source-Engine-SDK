#pragma once

class Utils
{
public:
	Utils()
	{

	}

	
};

class CNetVars
{
public:
	CNetVars()
	{
		_tables.clear();

		ClientClass* clientClass = Interfaces.Client->GetAllClasses();
		if (!clientClass)
		{
			printf("ERROR: ClientClass was not found\n");
			return;
		}

		while (clientClass)
		{
			RecvTable *recvTable = clientClass->m_pRecvTable;

			_tables.push_back(recvTable);

			clientClass = clientClass->m_pNext;
		}
	}

	int GetOffset(const char* tableName, const char* propName)
	{
		int offset = GetProp(tableName, propName);
		if (!offset)
		{
			printf("ERROR: Failed to find offset for prop: %s from table: %s", propName, tableName);
			return 0;
		}


		return offset;
	}

private:
	int GetProp(const char* tableName, const char* propName, RecvProp **prop = 0)
	{
		RecvTable* recvTable = GetTable(tableName);
		if (!recvTable)
		{
			printf("ERROR: Failed to find table: %s", tableName);
			return 0;
		}
		int offset = GetProp(recvTable, propName, prop);
		if (!offset)
		{
			printf("ERROR: Failed to find offset for prop: %s from table: %s", propName, tableName);
			return 0;
		}

		return offset;
	}
	int GetProp(RecvTable *recvTable, const char *propName, RecvProp **prop = 0)
	{
		int extraOffset = 0;
		for (int i = 0; i < recvTable->m_nProps; ++i)
		{
			RecvProp* recvProp = &recvTable->m_pProps[i];

			RecvTable *child = recvProp->m_pDataTable;

			if (child && (child->m_nProps > 0))
			{
				int tmp = GetProp(child, propName, prop);
				if (tmp)
				{
					extraOffset += (recvProp->m_Offset + tmp);
				}
			}

			if (_stricmp(recvProp->m_pVarName, propName))
				continue;
			if (prop)
			{
				*prop = recvProp;
			}
			return (recvProp->m_Offset + extraOffset);
		}
		return extraOffset;
	}

	RecvTable *GetTable(const char *tableName)
	{
		if (_tables.empty())
		{
			printf("ERROR: Failed to find table: %s (_tables is empty)\n", tableName);
			return 0;
		}

		for each (RecvTable* table in _tables)
		{
			if (!table)
				continue;
			if (_stricmp(table->m_pNetTableName, tableName) == 0)
				return table;
		}
		return 0;
	}

	std::vector<RecvTable*> _tables;
};

extern CNetVars* netVars;