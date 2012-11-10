 scm_make_gsubr(  "random?" ,  
	   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_random_p )); 
 scm_make_gsubr(  "make-random" ,  
	   0 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_make_random )); 
 scm_make_gsubr(  "seed-random!" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_seed_random )); 
 scm_make_gsubr(  "%random-integer!" ,  
	   3 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_random_int )); 
 scm_make_gsubr(  "%random-uniform!" ,  
	   3 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_random_uniform )); 
 scm_make_gsubr(  "%random-normal!" ,  
	   3 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_random_normal )); 
 scm_make_gsubr(  "%random-boolean!" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_random_bool )); 
