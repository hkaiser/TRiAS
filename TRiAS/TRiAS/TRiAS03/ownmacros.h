// own Macros
// since RETURN_FAILED_HRESULT was destroyed by an ASSERTION
// use this one in uncritical Situations (E_ABORT)

#define DO_RETURN_IF_FAILED(hr)\
	{						\
		if (FAILED(hr))		\
			return hr;		\
	}

