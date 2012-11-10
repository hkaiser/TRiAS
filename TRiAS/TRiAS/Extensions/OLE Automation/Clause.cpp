///////////////////////////////////////////////////////////////////////////
// Clause.cpp

#include "precomp.hxx"

#include "yy_ansi.h"
#include "yy_stdio.h"
#include "yy_strng.h"
#include "yy_stdlb.h"
#include "yy_asrt.h"
#include "yy_inpge.h"
#include "yy_mylex.h"
#include "yy_mypsr.h"

#include "clause.h"

///////////////////////////////////////////////////////////////////////////////
// Term
clause_rslt_ptr expr_term_base::clause_execute(EXECUTEMODE rgMode)
{
	ASSERT(FALSE);
	return NULL;
}

void expr_term_base::clause_list()
{
}

///////////////////////////////////////////////////////////////////////////////
// Compare
clause_rslt_ptr expr_compare_base::clause_execute(EXECUTEMODE rgMode)
{
	ASSERT(FALSE);
	return NULL;
}

void expr_compare_base::clause_list()
{
}

///////////////////////////////////////////////////////////////////////////////
// OBJPROPNAME IS NOT? NULL
clause_rslt_ptr expr_null::clause_execute(EXECUTEMODE rgMode)
{
clause_rslt_ptr temp1 = yy_this_operand[0].as_clause_ptr -> calc_execute();

	if (NULL == temp1 || temp1 -> m_rgType != RESULTTYPE_ObjectProperty) {
		yy_err_report(220);  // internal error

	clause_rslt_ptr *pResult = NULL;
		
		ATLTRY(pResult = new clause_rslt_obj()))
		return pResult;
	}

clause_rslt_ptr result = NULL;
EXECUTEMODE rgNewMode = EXECUTEMODE((rgMode & ~EXECUTEMODE_OpMask)|EXECUTEMODE_Exists);

	if (4 == yy_this_num_operands)
		rgNewMode = EXECUTEMODE(rgNewMode ^ EXECUTEMODE_Negate);

	ATLTRY(result = new term_rslt_obj (temp1, NULL, rgNewMode));
	if (NULL == result) {
		yy_err_report(406);  // no memory
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
		return NULL;		
	}

	delete temp1;
	if (!result -> IsValid()) {
		delete result;
		yy_err_report(220);  // internal error
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
		return NULL;		
	}
	return result;
}

void expr_null::clause_list()
{
}

///////////////////////////////////////////////////////////////////////////////
// NOT Term
clause_rslt_ptr expr_not::clause_execute(EXECUTEMODE rgMode)
{
EXECUTEMODE rgNewMode = EXECUTEMODE(rgMode ^ EXECUTEMODE_Negate);
clause_rslt_ptr temp1 = yy_this_operand[0].as_clause_ptr -> calc_execute (rgNewMode);

	if (NULL == temp1) {
		yy_err_report(220);  // internal error

	clause_rslt_ptr *pResult = NULL;
		
		ATLTRY(pResult = new clause_rslt_obj()))
		return pResult;
	}
    return temp1;
}

void expr_not::clause_list()
{
}

///////////////////////////////////////////////////////////////////////////////
// Term AND Term
clause_rslt_ptr expr_and::clause_execute(EXECUTEMODE rgMode)
{
// Operanden besorgen
clause_rslt_ptr temp1 = yy_this_operand[0].as_clause_ptr -> calc_execute();

	if (NULL == temp1) {
		yy_err_report(220);  // internal error

	clause_rslt_ptr *pResult = NULL;
		
		ATLTRY(pResult = new clause_rslt_obj()))
		return pResult;
	}

clause_rslt_ptr temp2 = yy_this_operand[1].as_clause_ptr -> calc_execute();

	if (NULL == temp2) {
		delete temp2;
		yy_err_report(220);  // internal error

	clause_rslt_ptr *pResult = NULL;
		
		ATLTRY(pResult = new clause_rslt_obj()))
		return pResult;
	}

// Operation ausführen
clause_rslt_ptr result = NULL;
EXECUTEMODE rgNewMode = EXECUTEMODE((rgMode & ~EXECUTEMODE_OpMask)|EXECUTEMODE_And);

	ATLTRY(result = new term_rslt_obj (temp1, temp2, rgNewMode));
	if (NULL == result) {
		yy_err_report(406);  // no memory
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
		return NULL;		
	}

	delete temp1;
	delete temp2;
	if (!result -> IsValid()) {
		delete result;
		yy_err_report(220);  // internal error
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
		return NULL;		
	}
	return result;
}

void expr_and::clause_list()
{
}

///////////////////////////////////////////////////////////////////////////////
// Term OR Term
clause_rslt_ptr expr_or::clause_execute(EXECUTEMODE rgMode)
{
// Operanden besorgen
clause_rslt_ptr temp1 = yy_this_operand[0].as_clause_ptr -> calc_execute();

	if (NULL == temp1) {
		yy_err_report(220);  // internal error

	clause_rslt_ptr *pResult = NULL;
		
		ATLTRY(pResult = new clause_rslt_obj()))
		return pResult;
	}

clause_rslt_ptr temp2 = yy_this_operand[1].as_clause_ptr -> calc_execute();

	if (NULL == temp2) {
		delete temp2;
		yy_err_report(220);  // internal error

	clause_rslt_ptr *pResult = NULL;
		
		ATLTRY(pResult = new clause_rslt_obj()))
		return pResult;
	}

// Operation ausführen
clause_rslt_ptr result = NULL;
EXECUTEMODE rgNewMode = EXECUTEMODE((rgMode & ~EXECUTEMODE_OpMask)|EXECUTEMODE_Or);

	ATLTRY(result = new term_rslt_obj (temp1, temp2, rgNewMode));
	if (NULL == result) {
		yy_err_report(406);  // no memory
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
		return NULL;		
	}

	delete temp1;
	delete temp2;
	if (!result -> IsValid()) {
		delete result;
		yy_err_report(220);  // internal error
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
		return NULL;		
	}
	return result;
}

void expr_or::clause_list()
{
}

///////////////////////////////////////////////////////////////////////////////
// '(' Term ')'
clause_rslt_ptr expr_nested::clause_execute(EXECUTEMODE rgMode)
{
    return yy_this_operand[1].as_clause_ptr -> calc_execute (rgMode);
}

void expr_nested::clause_list()
{
}

///////////////////////////////////////////////////////////////////////////////
// OBJPROPNAME NOT? EQUAL STRING_CONSTANT
clause_rslt_ptr expr_equal::clause_execute (EXECUTEMODE rgMode)
{
clause_rslt_ptr temp1 = yy_this_operand[0].as_clause_ptr -> calc_execute();

	if (NULL == temp1 || temp1 -> m_rgType != RESULTTYPE_ObjectProperty) {
		yy_err_report(220);  // internal error

	clause_rslt_ptr *pResult = NULL;
		
		ATLTRY(pResult = new clause_rslt_obj()))
		return pResult;
	}

int iIndex = (4 == yy_this_num_operands) ? 3 : 2;
string_ptr temp2 = yy_this_operand[iIndex].as_string_ptr -> yy_string();
clause_rslt_ptr result = NULL;
EXECUTEMODE rgNewMode = EXECUTEMODE((rgMode & ~EXECUTEMODE_OpMask)|EXECUTEMODE_Equal);

	ATLTRY(result = new term_rslt_obj (temp1, temp2, rgNewMode));
	if (NULL == result) {
		yy_err_report(406);  // no memory
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
		return NULL;		
	}

	delete temp1;
	if (!result -> IsValid()) {
		delete result;
		yy_err_report(220);  // internal error
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
		return NULL;		
	}
	return result;
}

void expr_equal::clause_list()
{
}

///////////////////////////////////////////////////////////////////////////////
// OBJPROPNAME NOT_EQUAL STRING_CONSTANT
clause_rslt_ptr expr_notequal::clause_execute(EXECUTEMODE rgMode)
{
clause_rslt_ptr temp1 = yy_this_operand[0].as_clause_ptr -> calc_execute();

	if (NULL == temp1 || temp1 -> m_rgType != RESULTTYPE_ObjectProperty) {
		yy_err_report(220);  // internal error

	clause_rslt_ptr *pResult = NULL;
		
		ATLTRY(pResult = new clause_rslt_obj()))
		return pResult;
	}

string_ptr temp2 = yy_this_operand[1].as_string_ptr -> yy_string();
clause_rslt_ptr result = NULL;
EXECUTEMODE rgNewMode = EXECUTEMODE(((rgMode & ~EXECUTEMODE_OpMask)|EXECUTEMODE_Equal) ^ EXECUTEMODE_Negate);

	ATLTRY(result = new term_rslt_obj (temp1, temp2, rgNewMode));
	if (NULL == result) {
		yy_err_report(406);  // no memory
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
		return NULL;		
	}

	delete temp1;
	if (!result -> IsValid()) {
		delete result;
		yy_err_report(220);  // internal error
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
		return NULL;		
	}
	return result;
}

void expr_notequal::clause_list()
{
}

///////////////////////////////////////////////////////////////////////////////
// OBJPROPNAME LIKE STRING_CONSTANT
clause_rslt_ptr expr_like::clause_execute(EXECUTEMODE rgMode)
{
clause_rslt_ptr temp1 = yy_this_operand[0].as_clause_ptr -> calc_execute();

	if (NULL == temp1 || temp1 -> m_rgType != RESULTTYPE_ObjectProperty) {
		yy_err_report(220);  // internal error

	clause_rslt_ptr *pResult = NULL;
		
		ATLTRY(pResult = new clause_rslt_obj()))
		return pResult;
	}

string_ptr temp2 = yy_this_operand[1].as_string_ptr -> yy_string();
clause_rslt_ptr result = NULL;
EXECUTEMODE rgNewMode = EXECUTEMODE((rgMode & ~EXECUTEMODE_OpMask)|EXECUTEMODE_Like);

	ATLTRY(result = new term_rslt_obj (temp1, temp2, rgNewMode));
	if (NULL == result) {
		yy_err_report(406);  // no memory
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
		return NULL;		
	}

	delete temp1;
	if (!result -> IsValid()) {
		delete result;
		yy_err_report(220);  // internal error
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
		return NULL;		
	}
	return result;
}

void expr_like::clause_list()
{
}

///////////////////////////////////////////////////////////////////////////////
// OBJPROPNAME NOT LIKE STRING_CONSTANT
clause_rslt_ptr expr_notlike::clause_execute(EXECUTEMODE rgMode)
{
clause_rslt_ptr temp1 = yy_this_operand[0].as_clause_ptr -> calc_execute();

	if (NULL == temp1 || temp1 -> m_rgType != RESULTTYPE_ObjectProperty) {
		yy_err_report(220);  // internal error

	clause_rslt_ptr *pResult = NULL;
		
		ATLTRY(pResult = new clause_rslt_obj()))
		return pResult;
	}

string_ptr temp2 = yy_this_operand[3].as_string_ptr -> yy_string();
clause_rslt_ptr result = NULL;
EXECUTEMODE rgNewMode = EXECUTEMODE(((rgMode & ~EXECUTEMODE_OpMask)|EXECUTEMODE_Like) ^ EXECUTEMODE_Negate);

	ATLTRY(result = new term_rslt_obj (temp1, temp2, rgNewMode));
	if (NULL == result) {
		yy_err_report(406);  // no memory
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
		return NULL;		
	}

	delete temp1;
	if (!result -> IsValid()) {
		delete result;
		yy_err_report(220);  // internal error
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
		return NULL;		
	}
	return result;
}

void expr_notlike::clause_list()
{
}

///////////////////////////////////////////////////////////////////////////////
// OBJPROPNAME REGEXPR STRING_CONSTANT
clause_rslt_ptr expr_regexpr::clause_execute(EXECUTEMODE rgMode)
{
clause_rslt_ptr temp1 = yy_this_operand[0].as_clause_ptr -> calc_execute();

	if (NULL == temp1 || temp1 -> m_rgType != RESULTTYPE_ObjectProperty) {
		yy_err_report(220);  // internal error

	clause_rslt_ptr *pResult = NULL;
		
		ATLTRY(pResult = new clause_rslt_obj()))
		return pResult;
	}

string_ptr temp2 = yy_this_operand[1].as_string_ptr -> yy_string();
clause_rslt_ptr result = NULL;
EXECUTEMODE rgNewMode = EXECUTEMODE((rgMode & ~EXECUTEMODE_OpMask)|EXECUTEMODE_RegExpr);

	ATLTRY(result = new term_rslt_obj (temp1, temp2, rgNewMode));
	if (NULL == result) {
		yy_err_report(406);  // no memory
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
		return NULL;		
	}

	delete temp1;
	if (!result -> IsValid()) {
		delete result;
		yy_err_report(220);  // internal error
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
		return NULL;		
	}
	return result;
}

void expr_regexpr::clause_list()
{
}

///////////////////////////////////////////////////////////////////////////////
// OBJPROPNAME 
clause_rslt_ptr expr_regexpr::clause_execute(EXECUTEMODE)
{
string_ptr temp1 = yy_this_operand[0].as_string_ptr -> yy_string();

	ATLTRY(result = new objprop_rslt_obj (temp1));
	if (NULL == result) {
		yy_err_report(406);  // no memory
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
		return NULL;		
	}

	delete temp1;
	if (!result -> IsValid()) {
		delete result;
		yy_err_report(220);  // internal error
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
		return NULL;		
	}
	return result;
}

void expr_regexpr::clause_list()
{
}

