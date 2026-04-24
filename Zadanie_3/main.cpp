/*-Задание-3. (наследуемый класс)-*/

#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

class SqlSelectQueryBuilder
{
protected:
  vector<string> columnNames = {};
  map<string, string> where = {};
  string from = "";

public:
  virtual ~SqlSelectQueryBuilder() {};

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

  virtual string BuildQuery()
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

class AdvancedSqlSelectQueryBuilder : public SqlSelectQueryBuilder
{
private:
  string signum = "";

public:
  AdvancedSqlSelectQueryBuilder &installSignum(const string &signum)
  {
    this->signum.clear();
    this->signum = signum;
    return *this;
  }

  string BuildQuery() override
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
        query += key + this->signum + value;
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

  string show()
  {
    return this->signum;
  }
};

int main()
{
  vector<string> namePhone = {"name", "phone"};
  map<string, string> where = {{"id", "42"}};

  SqlSelectQueryBuilder SQLB;
  SQLB.AddColumns(namePhone);
  SQLB.AddFrom("students");
  SQLB.AddWhere(where);
  cout << SQLB.BuildQuery() << endl;

  AdvancedSqlSelectQueryBuilder ASQL;
  ASQL.AddColumns(namePhone);
  ASQL.AddFrom("students");
  ASQL.AddWhere(where);
  ASQL.installSignum(">");
  cout << ASQL.BuildQuery() << endl;

  return 0;
}