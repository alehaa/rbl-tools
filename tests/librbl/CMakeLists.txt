# This file is part of rbl-tools.
#
# rbl-tools is free software: you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later
# version.
#
# rbl-tools is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
# A PARTICULAR PURPOSE. See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program. If not, see
#
#  http://www.gnu.org/licenses/
#
#
# Copyright (C)
#  2015-2017 Alexander Haase <ahaase@mksec.de>
#

include_directories(../../src/librbl)


#
# rbl_atoip
#

add_executable(test_librbl_atoip atoip.c)
target_link_libraries(test_librbl_atoip rbl_shared)

#
# IPv4
#

# Check incorrect length.
rbl_add_test(librbl_atoip_ipv4_missing1
	COMMAND test_librbl_atoip 1
	PASS_EXPRESSION "IP not valid")

rbl_add_test(librbl_atoip_ipv4_missing2
	COMMAND test_librbl_atoip 1.2
	PASS_EXPRESSION "IP not valid")

rbl_add_test(librbl_atoip_ipv4_missing3
	COMMAND test_librbl_atoip 1.2.3
	PASS_EXPRESSION "IP not valid")

rbl_add_test(librbl_atoip_ipv4_toolong
	COMMAND test_librbl_atoip 1.2.3.4.5
	PASS_EXPRESSION "IP not valid")

# An invalid IP with one group > 255.
rbl_add_test(librbl_atoip_ipv4_invalid_digits
	COMMAND test_librbl_atoip 255.255.255.256
	PASS_EXPRESSION "IP not valid")

# A valid IP with no bits set.
rbl_add_test(librbl_atoip_ipv4_valid_empty
	COMMAND test_librbl_atoip 0.0.0.0
	PASS_EXPRESSION "0.0.0.0")

# A valid sample IP.
rbl_add_test(librbl_atoip_ipv4_valid_simple
	COMMAND test_librbl_atoip 1.2.3.4
	PASS_EXPRESSION "4.3.2.1")

#
# IPv6
#

# Check incorrect length.
rbl_add_test(librbl_atoip_ipv6_missing1
	COMMAND test_librbl_atoip 0
	PASS_EXPRESSION "IP not valid")

rbl_add_test(librbl_atoip_ipv6_missing2
	COMMAND test_librbl_atoip 0:0
	PASS_EXPRESSION "IP not valid")

# Invalid shortening of IP.
rbl_add_test(librbl_atoip_ipv6_invalid_shortening
	COMMAND test_librbl_atoip 1::1::1
	PASS_EXPRESSION "IP not valid")

# Invalid charset
rbl_add_test(librbl_atoip_ipv6_invalid_chars
	COMMAND test_librbl_atoip ::g
	PASS_EXPRESSION "IP not valid")

# Valid examples
rbl_add_test(librbl_atoip_ipv6_valid_empty
	COMMAND test_librbl_atoip ::
	PASS_EXPRESSION
		"0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0")

rbl_add_test(librbl_atoip_ipv6_valid_simple1
	COMMAND test_librbl_atoip ::1:2:3:4
	PASS_EXPRESSION
		"4.0.0.0.3.0.0.0.2.0.0.0.1.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0")

rbl_add_test(librbl_atoip_ipv6_valid_simple2
	COMMAND test_librbl_atoip 1::2
	PASS_EXPRESSION
		"2.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.1.0.0.0")


#
# rbl_lookup_a
#

add_executable(test_librbl_lookup_a lookup_a.c)
target_link_libraries(test_librbl_lookup_a rbl_shared)

# Check without match
rbl_add_test(test_librbl_lookup_a_listed
	COMMAND test_librbl_lookup_a 127.0.0.2 zen.spamhaus.org
	PASS_EXPRESSION "is listed")

rbl_add_test(test_librbl_lookup_a_not_listed
	COMMAND test_librbl_lookup_a 0.0.0.0 zen.spamhaus.org
	PASS_EXPRESSION "is not listed")

rbl_add_test(test_librbl_lookup_a_match
	COMMAND test_librbl_lookup_a 127.0.0.2 zen.spamhaus.org
		127.0.0.2 127.0.0.4 127.0.0.10
	PASS_EXPRESSION "is listed")

rbl_add_test(test_librbl_lookup_a_no_match
	COMMAND test_librbl_lookup_a 127.0.0.2 zen.spamhaus.org 0.0.0.0
	PASS_EXPRESSION "is not listed")
