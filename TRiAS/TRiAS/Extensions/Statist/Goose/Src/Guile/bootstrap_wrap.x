 scm_make_gsubr(  "resample-thread-default" ,  
	   0 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_resamp_thread_def )); 
 scm_make_gsubr(  "resample-thread-default!" ,  
	   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_resamp_thread_def_bang )); 
 scm_make_gsubr(  "resample-mean" ,  
	   2 ,  1 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_resamp_mean )); 
 scm_make_gsubr(  "resample-med" ,  
	   2 ,  1 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_resamp_med )); 
 scm_make_gsubr(  "resample-sdev" ,  
	   2 ,  1 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_resamp_sdev )); 
