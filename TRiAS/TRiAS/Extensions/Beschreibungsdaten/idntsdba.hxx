// --------------------- ???????????? -----------------------------------------
// File: IDNTSDBA.HXX

#if !defined(_IDNTSDBA_HXX)
#define _IDNTSDBA_HXX

#if defined(_MSC_VER)// && defined(WRAP_ERR_OBJECT)
// Die folgenden Klassen dienen lediglich dazu, zu erzwingen, daß der für diese
// Klassen angeforderte Speicher über die richtige Speicherverwaltung freige-
// geben wird.
class yy_err_identsdb_obj : public yy_err_proc_obj {
public:
		yy_err_identsdb_obj (
			yy_err_procedure    yy_new_err_proc,
		        yy_errmsg_dflt_ptr  yy_new_err_tbl = NULL,
		        int                 yy_new_err_tbl_max = 0,
		        yy_synamsg_dflt_ptr yy_new_syna_tbl = NULL,
		        int                 yy_new_syna_tbl_max = 0)
			: yy_err_proc_obj (
				yy_new_err_proc,
				yy_new_err_tbl,
				yy_new_err_tbl_max,
				yy_new_syna_tbl,
				yy_new_syna_tbl_max) {}
				
		~yy_err_identsdb_obj (void) {}
};

class yy_inp_identsdb_obj : public yy_inp_file_obj {
public:
		yy_inp_identsdb_obj (yy_err_ptr yy_this_err_ptr) :
			yy_inp_file_obj (yy_this_err_ptr) {}
		~yy_inp_identsdb_obj (void) {}

};

#else
#define yy_err_identsdb_obj yy_err_proc_obj 
#define yy_inp_identsdb_obj	yy_inp_file_obj
#endif

#endif // _IDNTSDBA_HXX
