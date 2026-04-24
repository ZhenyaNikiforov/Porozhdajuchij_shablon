#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

class SqlSelectQueryBuilder
{
private:
  vector<string> columnNames = {};
  map<string, string> where = {};
  string from = "";

public:
  SqlSelectQueryBuilder &AddColumns(vector<string> &names)
  {
    for (int i = 0; i < names.size(); ++i)
    {
      this->columnNames.push_back(names[i]);
    }

    return *this;
  }

  SqlSelectQueryBuilder &AddWhere(map<string, string> &where)
  {
    for (const auto &[key, value] : where)
    {
      this->where[key] = value;
    }

    return *this;
  }

  SqlSelectQueryBuilder &AddFrom(const string &from)
  {
    this->from.clear();
    this->from = from;

    return *this;
  }

  string BuldQuery()
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
      for (int i = 0; i < columnNames.size(); ++i)
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

    query += "FROM " + this->from + " WHERE ";

    bool firstKey = true;
    for (const auto &[key, value] : this->where)
    {
      if (firstKey)
      {
        query += key + "=" + value;
        firstKey = false;
      }
      else
      {
        query += " AND " + key + "=" + value;
      }
    }
    query += ";";

    return query;
  }
};

int main()
{
  vector<string> namePhone = {"name", "phone"};
  map<string, string> where = {{"id", "42"}, {"name", "John"}};

  SqlSelectQueryBuilder SQLB;
  SQLB.AddColumns(namePhone);
  SQLB.AddFrom("students");
  SQLB.AddWhere(where);
  cout << SQLB.BuldQuery() << endl;

  return 0;
}