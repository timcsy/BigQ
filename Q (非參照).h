#ifndef Q_h
#define Q_h

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int gcd(int m,int n){if(m%n==0)return n;else return gcd(n,m%n);}

class Q
{
	friend int compare(Q a,Q b);
	friend Q operator+(Q a,Q b);
	friend Q operator+(Q a,int b){Q i(b);return a+i;}
	friend Q operator+(int a,Q b){return b+a;}
	friend Q operator-(Q a,Q b);
	friend Q operator-(Q a,int b){Q i(b);return a-i;}
	friend Q operator-(int a,Q b){return b-a;}
	friend Q operator*(Q a,Q b);
	friend Q operator*(Q a,int b){Q i(b);return a*i;}
	friend Q operator*(int a,Q b){return b*a;}
	friend Q operator/(Q a,Q b);
	friend Q operator/(Q a,int b){Q i(b);return a/i;}
	friend Q operator/(int a,Q b){return b/a;}
	friend bool operator>(int a,Q b){return b<a;}
	friend bool operator<(int a,Q b){return b>a;}
	friend bool operator>=(int a,Q b){return b<=a;}
	friend bool operator<=(int a,Q b){return b>=a;}
	friend bool operator==(int a,Q b){return b==a;}
	friend bool operator!=(int a,Q b){return b!=a;}
	friend ostream& operator<<(ostream& output,Q& a)
	{output<<a.toString();return output;}
	friend istream& operator>>(istream& input,Q& a)
	{string s;input>>s;a=Q(s);return input;}
	private:
		int p; //分母 
		int q; //分子 
		bool sign;
	public:
		Q();
		Q(int pp,int qq,bool sgn);
		Q(int n);
		Q(double d);
		Q(string s);
		int getp(){return p;}
		void setp(int pp){p=pp;}
		int getq(){return q;}
		void setq(int qq){q=qq;}
		bool getSign(){return sign;}
		void setSign(int sgn){sign=sgn;}
		void initial()
		{sign=1;p=1;q=0;}
		void renew();
		string toString();
		Q& operator+=(Q& b){*this=*this+b;return *this;}
		Q& operator+=(int b){*this=*this+b;return *this;}
		Q& operator-=(Q& b){*this=*this-b;return *this;}
		Q& operator-=(int b){*this=*this-b;return *this;}
		Q& operator*=(Q& b){*this=*this*b;return *this;}
		Q& operator*=(int b){*this=*this*b;return *this;}
		Q& operator/=(Q& b){*this=*this/b;return *this;}
		Q& operator/=(int b){*this=*this/b;return *this;}
		Q operator-(){Q c(*this);if(c!=0)c(0)=!c(0);return c;}
		Q& operator++(){*this+=1;return *this;}
		Q& operator--(){*this-=1;return *this;}
		Q operator++(int){Q t(*this);++*this;return t;}
		Q operator--(int){Q t(*this);--*this;return t;}
		bool operator>(Q b){return compare(*this,b)==1;}
		bool operator>(int b){Q i(b);return *this>i;}
		bool operator<(Q b){return compare(*this,b)==-1;}
		bool operator<(int b){Q i(b);return *this<i;}
		bool operator>=(Q b){return !(compare(*this,b)==-1);}
		bool operator>=(int b){Q i(b);return *this>=i;}
		bool operator<=(Q b){return !(compare(*this,b)==1);}
		bool operator<=(int b){Q i(b);return *this<=i;}
		bool operator==(Q b){return compare(*this,b)==0;}
		bool operator==(int b){Q i(b);return *this==i;}
		bool operator!=(Q b){return compare(*this,b)!=0;}
		bool operator!=(int b){Q i(b);return *this!=i;}
		int& operator [](int i)
		{if(i==1)return p;else if(i==2)return q;}
		bool& operator ()(int i)
		{if(i==0)return sign;}
		void print(string name);
		operator double(){return (sign?1:-1)*(double)q/(double)p;}
};
Q::Q()
{
	initial();
}
Q::Q(int pp,int qq,bool sgn)
{
	initial();
	p=pp; q=qq; sign=sgn;
	renew();
}
Q::Q(int n)
{
	initial();
	sign=(n>=0)?1:0;
	q=(n>=0)?n:-n;
	renew();
}
Q::Q(double d)
{
	initial();
	sign=(d>=0)?1:0;
	d=(d>=0)?d:-d;
	int t=1;
	while(d!=(int)d){if(t%10)t*=10;else t=10;d*=10;}
	q=d; p=t;
	renew();
}
Q::Q(string s)
{
	initial();
	if(s[0]!='-' && s[0]!='+') q=s[0]-48;
	bool b=1;
	for(int i=1;i<s.length();i++)
	{
		if(s[i]=='/') b=0;
		if(b) q=q*10+(s[i]-48);
		else p=p*10+(s[i]-48);
	}
	if(s[0]=='-') sign=0;
	renew();
}
void Q::renew()
{
	sign=!((!((p>=0?1:0)^(q>=0?1:0)))^sign);
	if(p<0) p=-p; if(q<0) q=-q;
	if(q==0){p=1;sign=1;}
	else
	{
		int g=gcd(p,q);
		p/=g; q/=g;
	}
}
string Q::toString()
{
	stringstream ss;
	string s;
	if(sign==0) ss<<"-";
	if(p==1) ss<<q;
	else ss<<q<<"/"<<p;
	ss>>s;
	return s;
}
void Q::print(string name)
{
	cout<<"Q "<<name<<":"<<endl;
	cout<<" sign = "<<sign<<endl;
	cout<<" p = "<<p<<endl;
	cout<<" q = "<<q<<endl;
}
//define friend functions
int compare(Q a,Q b)
{
	int m=a(0)?1:-1;
	int n=b(0)?1:-1;
	if(m*n==-1) return m;
	else
	{
		if(b[1]*a[2]-a[1]*b[2]>0) return 1*m;
		if(b[1]*a[2]-a[1]*b[2]<0) return -1*m;
		else return 0;
	}
}
Q operator+(Q a,Q b)
{
	Q c;
	if(a(0)^b(0)==0)
	{
		c(0)=a(0);
		c[1]=a[1]*b[1];
		c[2]=b[1]*a[2]+a[1]*b[2];
		c.renew();
	}
	else if(a(0)==1 && b(0)==0) c=a-(-b);
	else  c=b-(-a);
	return c;
}
Q operator-(Q a,Q b)
{
	Q c;
	if(a(0)^b(0)==0)
	{
		c(0)=a(0);
		c[1]=a[1]*b[1];
		c[2]=b[1]*a[2]-a[1]*b[2];
		c.renew();
	}
	else
	{
		b(0)=!b(0);
		c=a+b;
		b(0)=!b(0);
	}
	return c;
}
Q operator*(Q a,Q b)
{
	Q c;
	c(0)=!(a(0)^b(0));
	c[1]=a[1]*b[1];
	c[2]=a[2]*b[2];
	c.renew();
	return c;
}
Q operator/(Q a,Q b)
{
	if(b==0) throw "除數為零";
	else
	{
		Q c;
		c(0)=!(a(0)^b(0));
		c[1]=a[1]*b[2];
		c[2]=a[2]*b[1];
		c.renew();
		return c;
	}
}
#endif
