Summary: Object-Relational Database Management System
Name: GigaBASE
Version: 1.15
Release: 2
Copyright: distributable
Group: Applications/Databases
Source: gigabase-1.15.tar.gz
%description
Gigabase builtin object-relational database engine tightly
integrated with C++ language. It support query language (subset of SQL),
logless transactions, zero-time recovery, automatic scheme evaluation.

%prep
%setup -c

%build
make

%install
make install

%files
/usr/local/gigabase
