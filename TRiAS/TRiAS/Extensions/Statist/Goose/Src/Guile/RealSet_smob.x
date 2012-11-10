 scm_make_gsubr(  "realset?" ,  
	   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_realsetp )); 
 scm_make_gsubr(  "make-realset" ,  
	   0 ,  0 ,  1 , reinterpret_cast<SCM(*)(...)>(scm_fn_make_realset )); 
 scm_make_gsubr(  "realset-label" ,  
	   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rs_label )); 
 scm_make_gsubr(  "realset-set-label!" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rs_set_label )); 
 scm_make_gsubr(  "realset-clone" ,  
	   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_realset_clone )); 
 scm_make_gsubr(  "realset-add!" ,  
	   1 ,  0 ,  1 , reinterpret_cast<SCM(*)(...)>(scm_fn_realset_add )); 
 scm_make_gsubr(  "realset-append!" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_realset_append )); 
 scm_make_gsubr(  "realset-size" ,  
	   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_realset_size )); 
 scm_make_gsubr(  "realset-ref" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_realset_ref )); 
 scm_make_gsubr(  "realset-sorted-ref" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_realset_sorted_ref )); 
 scm_make_gsubr(    "realset-min"  ,   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rsfunc_min  )); 
 scm_make_gsubr(    "realset-max"  ,   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rsfunc_max  )); 
 scm_make_gsubr(    "realset-range"  ,   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rsfunc_range  )); 
 scm_make_gsubr(    "realset-sum"  ,   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rsfunc_sum  )); 
 scm_make_gsubr(    "realset-mean"  ,   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rsfunc_mean  )); 
 scm_make_gsubr(    "realset-var"  ,   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rsfunc_var  )); 
 scm_make_gsubr(    "realset-sdev"  ,   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rsfunc_sdev  )); 
 scm_make_gsubr(    "realset-sdevs"  ,   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rsfunc_sdevs  )); 
 scm_make_gsubr(  "realset-percentile" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_realset_percentile )); 
 scm_make_gsubr(    "realset-med"  ,   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rsfunc_med  )); 
 scm_make_gsubr(    "realset-q1"  ,   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rsfunc_q1  )); 
 scm_make_gsubr(    "realset-q3"  ,   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rsfunc_q3  )); 
 scm_make_gsubr(    "realset-iqr"  ,   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rsfunc_iqr  )); 
 scm_make_gsubr(  "realset-decile" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_realset_decile )); 
 scm_make_gsubr(  "realset-mean-trimmed" ,  
	   2 ,  1 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_mean_trimmed )); 
 scm_make_gsubr(  "realset-mean-winsorized" ,  
	   2 ,  1 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_mean_winsorized )); 
 scm_make_gsubr(  "realset-moment" ,  
	   2 ,  1 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_moment )); 
 scm_make_gsubr(    "realset-gmean"  ,   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rsfunc_gmean  )); 
 scm_make_gsubr(    "realset-hmean"  ,   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rsfunc_hmean  )); 
 scm_make_gsubr(    "realset-rms"  ,   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rsfunc_rms  )); 
 scm_make_gsubr(    "realset-meandev"  ,   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rsfunc_meandev  )); 
 scm_make_gsubr(    "realset-meddev"  ,   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rsfunc_meddev  )); 
 scm_make_gsubr(    "realset-kurtosis"  ,   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rsfunc_kurtosis  )); 
 scm_make_gsubr(    "realset-skewness"  ,   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rsfunc_skewness  )); 
 scm_make_gsubr(    "realset-excess-kurtosis"  ,   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rsfunc_excess_kurtosis  )); 
 scm_make_gsubr(    "realset-momental-skewness"  ,   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rsfunc_momental_skewness  )); 
 scm_make_gsubr(    "realset-durbin-watson"  ,   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rsfunc_durbin_watson  )); 
 scm_make_gsubr(    "realset-AR1-independence-z"  ,   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rsfunc_AR1_independence_z  )); 
 scm_make_gsubr(  "realset-autocorr" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_autocorr )); 
 scm_make_gsubr(  "realset-autocorr-z" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_autocorr_z )); 
 scm_make_gsubr(  "realset-cramer-von-mises" ,  
	   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_cvm )); 
 scm_make_gsubr(  "realset-anderson-darling" ,  
	   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_anddar )); 
 scm_make_gsubr(  "realset-gmean-threshold" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_gmeanthresh )); 
 scm_make_gsubr(  "realset-covar" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_covar )); 
 scm_make_gsubr(  "realset-corr" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_corr )); 
 scm_make_gsubr(  "realset-spearman-rho" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_spearrho )); 
 scm_make_gsubr(  "realset-kendall-tau" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_kentau )); 
 scm_make_gsubr(  "realset-EDF-D+" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_edf_Dp )); 
 scm_make_gsubr(  "realset-EDF-D-" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_edf_Dm )); 
 scm_make_gsubr(  "realset-EDF-D" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_edf_D )); 
 scm_make_gsubr(  "realset-EDF-kuiper-V" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_edf_kv )); 
 scm_make_gsubr(  "realset-pooled-mean" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_pooled_mean )); 
 scm_make_gsubr(  "realset-pooled-var" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_pooled_var )); 
 scm_make_gsubr(  "realset-weighted-mean" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_wtd_mean )); 
 scm_make_gsubr(  "realset-sort!" ,  
	   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rs_sort )); 
 scm_make_gsubr(  "realset-linear-transform!" ,  
	   3 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rs_lin_trans )); 
 scm_make_gsubr(  "realset-log-transform!" ,  
	   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rs_log_trans )); 
 scm_make_gsubr(  "realset-exp-transform!" ,  
	   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rs_exp_trans )); 
 scm_make_gsubr(  "realset-logit-transform!" ,  
	   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rs_logit_trans )); 
 scm_make_gsubr(  "realset-reverse!" ,  
	   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rs_reverse )); 
 scm_make_gsubr(  "realset-scramble!" ,  
	   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rs_scramble )); 
 scm_make_gsubr(  "realset-rank!" ,  
	   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rs_rank )); 
 scm_make_gsubr(  "realset-standardize!" ,  
	   1 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rs_std )); 
 scm_make_gsubr(  "realset-greater-than" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rs_gt )); 
 scm_make_gsubr(  "realset-less-than" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rs_lt )); 
 scm_make_gsubr(  "realset-between" ,  
	   3 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rs_between )); 
 scm_make_gsubr(  "realset-equal-to" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rs_eq )); 
 scm_make_gsubr(  "realset+" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rs_set_add )); 
 scm_make_gsubr(  "realset-" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rs_set_sub )); 
 scm_make_gsubr(  "realset*" ,  
	   2 ,  0 ,  0 , reinterpret_cast<SCM(*)(...)>(scm_fn_rs_set_mul )); 
