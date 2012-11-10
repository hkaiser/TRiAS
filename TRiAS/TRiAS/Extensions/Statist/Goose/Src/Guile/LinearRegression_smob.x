 scm_make_gsubr(  "linear-regression?" ,  
	   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_linreg_p )); 
 scm_make_gsubr(  "linear-regression" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_do_linreg )); 
 scm_make_gsubr(  "linear-regression-slope" ,  
	   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_linreg_slope )); 
 scm_make_gsubr(  "linear-regression-intercept" ,  
	   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_linreg_int )); 
 scm_make_gsubr(  "linear-regression-correlation" ,  
	   1 ,   0 ,   0 , reinterpret_cast<SCM(*)(...)>(scm_fn_linreg_corr )); 
 scm_make_gsubr(  "linear-regression-predict" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_linreg_predict )); 
 scm_make_gsubr(  "linear-regression-slope-interval" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_linreg_slope_ci )); 
 scm_make_gsubr(  "linear-regression-intercept-interval" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_linreg_int_ci )); 
 scm_make_gsubr(  "linear-regression-correlation-interval" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_linreg_corr_ci )); 
 scm_make_gsubr(  "linear-regression-predict-interval" ,  
	   3 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_linreg_pred_ci )); 
 scm_make_gsubr(  "linear-regression-t" ,  
	   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_linreg_ind_t )); 
 scm_make_gsubr(  "linear-regression-p" ,  
	   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_linreg_ind_p )); 
