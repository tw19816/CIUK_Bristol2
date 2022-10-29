<?php

/*
	Phoronix Test Suite
	URLs: http://www.phoronix.com, http://www.phoronix-test-suite.com/
	Copyright (C) 2020, Phoronix Media
	Copyright (C) 2020, Michael Larabel

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

class debug_time implements pts_option_interface
{
	const doc_skip = true;
	const doc_section = '';
	const doc_description = "";

	public static function run($r)
	{
		echo pts_client::cli_just_bold('Current Date/Time: ') . date('Y-m-d H:i:s', pts_client::current_time()) . PHP_EOL;
	}
}

?>
