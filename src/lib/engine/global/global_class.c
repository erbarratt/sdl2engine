#include "global_pub.h"
#include "global_class.h"

/**
* Instantiate global Object
* @param void* eOBJ self
* @return void
*/
	void global_t_instantiate(void * eOBJ)
	{
		eSELF(global_t);

		//define props
			self->render = eNEW(render_t);
			eCONSTRUCT(render_t, self->render);

		//define props
			self->render = eNEW(render_t);
			eCONSTRUCT(render_t, self->render);

	}

