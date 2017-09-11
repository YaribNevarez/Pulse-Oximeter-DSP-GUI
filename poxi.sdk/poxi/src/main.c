/*
 * main.c
 *
 *  Created on: 13 de feb. de 2017
 *      Author: Yarib Nev�rez
 */

#include "poxi.h"

int main()
{
	int rc;

	Poxi * App = Poxi_instance();

	rc = App != NULL;

	if (rc)
	{
		rc = App->initialize();

		if (rc)
		{
			rc = App->run();
		}

		App->dispose();
	}

	return rc;
}
