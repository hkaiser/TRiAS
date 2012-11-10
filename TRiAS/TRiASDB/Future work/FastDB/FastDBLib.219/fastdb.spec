Summary: Main Memory Object-Relational Database Management System
Name: FastDB
Version: 1.15
Release: 1
Copyright: distributable
Group: Applications/Databases
Source: fastdb-1.15.tar.gz
%description
FastDB is highly efficient main memory database system 
with realtime capabilities and convenient C++ interface.
High speed of query 
execution is provided by elimination of data transfer overhead and
very effective locking implementation. Database file is mapped to virtual
memory space of each application working with database. So query is executed in
the context of application, requiring no context switching and data transfer.

%prep
%setup -c

%build
make

%install
make install

%files
/usr/local/fastdb


