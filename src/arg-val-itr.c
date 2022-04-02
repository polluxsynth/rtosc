#include <rtosc/arg-val-itr.h>
#include <rtosc/arg-val-math.h>

void rtosc_arg_val_itr_init(rtosc_arg_val_itr* itr,
			    const rtosc_arg_val_t* av)
{
    itr->av = av;
    itr->i = itr->range_i = 0;
}

const rtosc_arg_val_t* rtosc_arg_val_itr_get(const rtosc_arg_val_itr *itr,
    rtosc_arg_val_t* buffer)
{
    const rtosc_arg_val_t* result;
    if(itr->av->type == '-')
    {
	if(itr->av->val.r.has_delta)
	    rtosc_arg_val_range_arg(itr->av, itr->range_i, buffer);
	else
	    *buffer = itr->av[1];
	result = buffer;
    }
    else result = itr->av;
    return result;
}

void rtosc_arg_val_itr_next(rtosc_arg_val_itr *itr)
{
    // increase the range index
    if(itr->av->type == '-')
    {
	// increase if the limit was reached, and the limit was not infinity (=0)
	if(++itr->range_i >= itr->av->val.r.num && itr->av->val.r.num)
	{
	    if(itr->av->val.r.has_delta)
	    {
		++itr->av;
		++itr->i;
	    }
	    ++itr->av;
	    ++itr->i;
	    itr->range_i = 0;
	}
    }

    // if not inside a range (or at its beginning), increase the index
    if(!itr->range_i)
    {
	if(itr->av->type == 'a')
	{
	    itr->i += itr->av->val.a.len;
	    itr->av += itr->av->val.a.len;
	}
	++itr->i;
	++itr->av;
    }
}



