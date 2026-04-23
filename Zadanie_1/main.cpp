#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

class SqlSelectQueryBuilder
{
private:
  vector<string> columnNames;
  string tableName = "";
  map<string, string> where;

public:
  SqlSelectQueryBuilder &AddColumn(string columnName)
  {
    this->columnNames.push_back(columnName);
    return *this;
  }

  SqlSelectQueryBuilder &AddFrom(string tableName)
  {
    this->tableName = tableName;
    return *this;
  }

  SqlSelectQueryBuilder &AddWhere(string columnName, string value)
  {
    this->where[columnName] = value;
    return *this;
  }

  string BuildQuery()
  {
    string query = "";
    query += "SELECT ";

    if (this->columnNames.size() == 0)
    {
      query += "* ";
    }
    else
    {
      bool first = true;
      for (int i = 0; i < this->columnNames.size(); ++i)
      {
        if (first)
        {
          query += columnNames[i];
          first = false;
        }
        else
        {
          query += ", " + columnNames[i];
        }
      }
      query += " ";
    }

    query += "FROM " + this->tableName + " WHERE ";

    bool firstMap = true;
    for (const auto &[columnName, value] : this->where)
    {
      if (firstMap)
      {
        query += columnName + "=" + value;
        firstMap = false;
      }
      else
      {
        query += " AND " + columnName + "=" + value;
      }
    }
    query += ";";
    return query;
  }
};

int main()
{
  SqlSelectQueryBuilder SQLR;
  SQLR.AddColumn("name").AddColumn("phone");
  SQLR.AddFrom("students");
  SQLR.AddWhere("id", "42").AddWhere("name", "John");
  cout << SQLR.BuildQuery() << endl;
  return 0;
}