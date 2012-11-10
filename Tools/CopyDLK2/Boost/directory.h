// -*-C++-*- directory.h
// <!!----------------------------------------------------------------------> 
// <!! Copyright (C) 1998 Dietmar Kuehl, Claas Solutions GmbH > 
// <!!> 
// <!! Permission to use, copy, modify, distribute and sell this > 
// <!! software for any purpose is hereby granted without fee, provided > 
// <!! that the above copyright notice appears in all copies and that > 
// <!! both that copyright notice and this permission notice appear in > 
// <!! supporting documentation. Dietmar Kuehl and Claas Solutions make no > 
// <!! representations about the suitability of this software for any > 
// <!! purpose. It is provided "as is" without express or implied warranty. > 
// <!!----------------------------------------------------------------------> 

// Author: Dietmar Kuehl dietmar.kuehl@claas-solutions.de 
// Title:  An input iterator used to list the entries in a directory 
// Version: $Name: Release-1-0 $ $Id: directory.h,v 1.7 1998/11/11 03:06:13 kuehl Exp $

// -------------------------------------------------------------------------- 

#if !defined(BOOST_DIRECTORY_H)
#define BOOST_DIRECTORY_H 1

// --------------------------------------------------------------------------

#include <iterator>
#include <string>
#include <ctime>
#include <stdexcept>
#include "boost.h"

#if defined(unix) || defined(__unix) || defined(__unix__)
#  define BOOST_UNIX 1
#elif defined(_WINDOWS) || defined(_CONSOLE)
#  define BOOST_WINNT 1
#endif 

#include "io.h"
#include "direct.h"

// --------------------------------------------------------------------------

namespace boost
{
	namespace filesystem
	{
		class dir_it;

		template <class Property> class get;
		template <class Property> class set;

		class BOOST_DECL dir_it
		:   public std::iterator<std::input_iterator_tag, std::string>
		{
			struct representation;
			
		public:
			typedef ptrdiff_t   difference_type;
			typedef string value_type;
			typedef string *pointer;
			typedef string &reference;
			
			class proxy
			{
				friend dir_it;
				proxy(string const &ent): entry(ent) {}
			public:
				string operator*() const { return entry; }
			private:
				string entry;
			};
			
			dir_it();
			dir_it(string const &);
			dir_it(string const &, string const &);
			dir_it(dir_it const &);
			~dir_it();
			dir_it &operator= (dir_it const &);
			
			string operator* () const;
			dir_it      &operator++ ();
			proxy       operator++ (int);
			
			bool operator== (dir_it const &) const;
			bool operator!= (dir_it const &) const;

			representation *rep;
		};
		
        struct dir_it::representation
        {
	        representation():
		        m_handle(-1),
		        m_refcount(1)
	        {
	        }

	        representation(string const &dirname):
		        m_handle(_findfirst((dirname + "\\*").c_str(), &m_data)),
		        m_refcount(1)
	        {
	        }

	        representation(string const &dirname, string const &pattern):
		        m_handle(_findfirst((dirname + "\\" + pattern).c_str(), &m_data)),
		        m_refcount(1)
	        {
	        }

	        ~representation() { if (m_handle != -1) _findclose(m_handle); }

	        representation *reference()
	        {
		        ++m_refcount;
		        return this;
	        }
	        representation *release() { return --m_refcount? 0: this; }

	        representation &operator++()
	        {
		        if (m_handle != -1)
			        {
				        if (_findnext(m_handle, &m_data) == -1)
					        {
						        _findclose(m_handle);
						        m_handle = -1;
					        }

			        }

		        return *this;
	        }

	        bool operator== (representation const &rep) const
	        {
		        return (m_handle == -1) == (rep.m_handle == -1);
	        }

	        string operator* () { return m_data.name; }


	        struct _finddata_t const &get_data() const
	        {
		        return m_data;
	        }

        private:
	        struct _finddata_t m_data;
	        long               m_handle;
	        int                m_refcount;
	        string        m_directory;
        };

		struct size { typedef size_t value_type; };
		struct mtime { typedef time_t const *value_type; };

		struct is_directory { typedef bool value_type; };
		struct is_regular { typedef bool value_type; };
		struct is_hidden { typedef bool value_type; };

		struct user_read { typedef bool value_type; };
		struct user_write { typedef bool value_type; };
		struct user_execute { typedef bool value_type; };

		template <> class BOOST_DECL get<size>
		{
			typedef size::value_type value_type;
			
		public:
			get(dir_it const &it): m_it(it) {}
			operator value_type() const
		    {
			    return m_it.rep->get_data().size;
		    }
		    
		private:
			dir_it const &m_it;
		};

		template <> class BOOST_DECL get<mtime>
		{
			typedef mtime::value_type value_type;
			
		public:
			get(dir_it const &it): m_it(it) {}
			operator value_type() const
		    {
			    return &m_it.rep->get_data().time_write;
		    }
		    
		private:
			dir_it const &m_it;
		};

		template <> class BOOST_DECL get<is_directory>
		{
			typedef is_directory::value_type value_type;
			
		public:
			get(dir_it const &it): m_it(it) {}
			operator value_type() const
		    {
			    return (m_it.rep->get_data().attrib & _A_SUBDIR) != 0;
		    }
		    
		private:
			dir_it const &m_it;
		};

		template <> class BOOST_DECL get<is_regular>
		{
			typedef is_regular::value_type value_type;
			
		public:
			get(dir_it const &it): m_it(it) {}
			operator value_type() const
		    {
			    return (m_it.rep->get_data().attrib & _A_SUBDIR) == 0;
		    }
		    
		private:
			dir_it const &m_it;
		};

		template <> class BOOST_DECL get<is_hidden>
		{
			typedef is_hidden::value_type value_type;
			
		public:
			get(dir_it const &it): m_it(it) {}
			operator value_type() const
		    {
			    return (m_it.rep->get_data().attrib & _A_HIDDEN) != 0;
		    }
		    
		private:
			dir_it const &m_it;
		};
		template <> class BOOST_DECL set<is_hidden>
		{
		public:
			set(dir_it const &, is_hidden::value_type);
		};

		template <> class BOOST_DECL get<user_read>
		{
			typedef user_read::value_type value_type;
			
		public:
			get(dir_it const &it): m_it(it) {}
			operator value_type() const
		    {
			    return true;
		    }
		    
		private:
			dir_it const &m_it;
		};

		template <> class BOOST_DECL get<user_write>
		{
			typedef user_write::value_type value_type;
			
		public:
			get(dir_it const &it): m_it(it) {}
			operator value_type() const
		    {
			    return (m_it.rep->get_data().attrib & _A_RDONLY) == 0;
		    }
		    
		private:
			dir_it const &m_it;
		};
		template <> class BOOST_DECL set<user_write>
		{
		public:
			set(dir_it const &, user_write::value_type);
		};

		template <> class BOOST_DECL get<user_execute>
		{
			typedef user_execute::value_type value_type;
			
		public:
			get(dir_it const &it): m_it(it) {}
			operator value_type() const
		    {
			    string name(*m_it);
			    string ext(name.substr(name.find_last_of('.')));
			    return ext == ".exe" || ext == ".bat";
		    }
		    
		private:
			dir_it const &m_it;
		};

	} // namespace filesystem
} // namespace boost

namespace std
{
	template<>
	struct iterator_traits<boost::filesystem::dir_it>
	{
	public:
		typedef ptrdiff_t          difference_type;
		typedef string             value_type;
		typedef string             *pointer;
		typedef string             &reference;
		typedef input_iterator_tag iterator_category;
	};
} // namespace std

// --------------------------------------------------------------------------

#endif /* BOOST_DIRECTORY_H */
