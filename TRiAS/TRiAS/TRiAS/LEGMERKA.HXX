// --------------------- ???????????? -----------------------------------------
// File: LEGMERKA.HXX

#if !defined(_LEGMERKA_HXX)
#define _LEGMERKA_HXX

#if defined(MSCC8) || MSC_VER > 1020
// Die folgenden Klassen dienen lediglich dazu, zu erzwingen, daß der für diese
// Klassen angeforderte Speicher über die richtige Speicherverwaltung freige-
// geben wird.
class yy_err_LegendProc_obj : public yy_err_proc_obj {
public:
		yy_err_LegendProc_obj (
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
				
		~yy_err_LegendProc_obj (void) {}
};

class yy_inp_LegendString_obj : public yy_inp_string_obj {
public:
		yy_inp_LegendString_obj (yy_err_ptr yy_this_err)
			: yy_inp_string_obj (yy_this_err) {}
					
		~yy_inp_LegendString_obj (void) {}
};
#else
#define	yy_inp_LegendString_obj yy_inp_string_obj
#define yy_err_LegendProc_obj 	yy_err_proc_obj 
#endif

#endif // _LEGMERKA_HXX
