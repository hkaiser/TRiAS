 scm_make_gsubr(  "pest-normal-mean" ,  
	   4 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_pest_normal_mean )); 
 scm_make_gsubr( 
	   "pest-normal-difference-of-means-equal-sdev" ,  
	   6 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_pest_d_mean_eq_sd )); 
 scm_make_gsubr(  "pest-normal-variance" ,  
	   3 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_pest_normal_var )); 
 scm_make_gsubr(  "pest-normal-correlation" ,  
	   3 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_pest_normal_corr )); 
 scm_make_gsubr(  "pest-binomial-p-normal-approx" ,  
	   3 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_pest_bin_p_normal_approx )); 
 scm_make_gsubr(  "pest-binomial-p-normal-approx-alt" ,  
	   3 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_pest_bin_p_normal_approx_alt )); 
 scm_make_gsubr(  "pest-binomial-p-arcsin-method" ,  
	   3 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_pest_bin_p_arcsin )); 
