/*-
 * SSLproxy
 *
 * Copyright (c) 2017-2021, Soner Tari <sonertari@gmail.com>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "attrib.h"
#include "opts.h"
#include "filter.h"

#include <check.h>
#include <unistd.h>

START_TEST(set_filter_struct_01)
{
	char *s;
	int rv;
	opts_t *opts = opts_new();
	conn_opts_t *conn_opts = conn_opts_new();

	tmp_opts_t *tmp_opts = malloc(sizeof (tmp_opts_t));
	memset(tmp_opts, 0, sizeof (tmp_opts_t));

	FILE *f;
	unsigned int line_num = 0;

	// ATTENTION: We can use const strings here, because we do not modify s in load_filterrule_struct()
	s = "Action Divert\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nSrcIp *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nSrcIp *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nSrcIp *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nSrcIp *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nSrcIp *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// "Divert to *" one line rule is equivalent to "Action Divert\n}" struct rule (so are the rules for the other actions)

	s = "Action Divert\nLog *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nLog *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nLog *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nLog *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nLog *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	opts_free(opts);
	conn_opts_free(conn_opts);
	tmp_opts_free(tmp_opts);
}
END_TEST

START_TEST(set_filter_struct_02)
{
	char *s;
	int rv;
	opts_t *opts = opts_new();
	conn_opts_t *conn_opts = conn_opts_new();

	tmp_opts_t *tmp_opts = malloc(sizeof (tmp_opts_t));
	memset(tmp_opts, 0, sizeof (tmp_opts_t));

	FILE *f;
	unsigned int line_num = 0;

	s = "Action Divert\nSrcIp 192.168.0.1\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nSrcIp 192.168.0.1\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nSrcIp 192.168.0.1\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nSrcIp 192.168.0.1\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nSrcIp 192.168.0.1\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nSrcIp 192.168.0.1*\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nSrcIp 192.168.0.1*\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nSrcIp 192.168.0.1*\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nSrcIp 192.168.0.1*\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nSrcIp 192.168.0.1*\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = strdup("$macro 192.168.0.1 192.168.0.2 192.168.0.1* 192.168.0.2*");
	rv = filter_macro_set(opts, s, 0);
	fail_unless(rv == 0, "failed to set macro");
	free(s);


	s = "Action Divert\nSrcIp $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nSrcIp $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nSrcIp $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nSrcIp $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nSrcIp $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	opts_free(opts);
	conn_opts_free(conn_opts);
	tmp_opts_free(tmp_opts);
}
END_TEST

#ifndef WITHOUT_USERAUTH
START_TEST(set_filter_struct_03)
{
	char *s;
	int rv;
	opts_t *opts = opts_new();
	conn_opts_t *conn_opts = conn_opts_new();

	s = strdup("$macro root daemon admin*");
	rv = filter_macro_set(opts, s, 0);
	fail_unless(rv == 0, "failed to set macro");
	free(s);

	close(2);

	tmp_opts_t *tmp_opts = malloc(sizeof (tmp_opts_t));
	memset(tmp_opts, 0, sizeof (tmp_opts_t));

	FILE *f;
	unsigned int line_num = 0;

	s = "Action Divert\nUser *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == -1, "failed to parse rule");

	s = "Action Split\nUser *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == -1, "failed to parse rule");

	s = "Action Pass\nUser *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == -1, "failed to parse rule");

	s = "Action Block\nUser *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == -1, "failed to parse rule");

	s = "Action Match\nUser *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == -1, "failed to parse rule");


	s = "Action Divert\nUser *\nDesc desc\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == -1, "failed to parse rule");

	s = "Action Split\nUser *\nDesc desc\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == -1, "failed to parse rule");

	s = "Action Pass\nUser *\nDesc desc\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == -1, "failed to parse rule");

	s = "Action Block\nUser *\nDesc desc\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == -1, "failed to parse rule");

	s = "Action Match\nUser *\nDesc desc\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == -1, "failed to parse rule");


	s = "Action Divert\nUser $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == -1, "failed to parse rule");

	s = "Action Split\nUser $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == -1, "failed to parse rule");

	s = "Action Pass\nUser $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == -1, "failed to parse rule");

	s = "Action Block\nUser $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == -1, "failed to parse rule");

	s = "Action Match\nUser $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == -1, "failed to parse rule");


	s = "Action Divert\nUser $macro\nDesc desc\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == -1, "failed to parse rule");

	s = "Action Split\nUser $macro\nDesc desc\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == -1, "failed to parse rule");

	s = "Action Pass\nUser $macro\nDesc desc\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == -1, "failed to parse rule");

	s = "Action Block\nUser $macro\nDesc desc\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == -1, "failed to parse rule");

	s = "Action Match\nUser $macro\nDesc desc\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == -1, "failed to parse rule");


	s = "Action Divert\nUser $macro\nDesc $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == -1, "failed to parse rule");

	s = "Action Split\nUser $macro\nDesc $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == -1, "failed to parse rule");

	s = "Action Pass\nUser $macro\nDesc $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == -1, "failed to parse rule");

	s = "Action Block\nUser $macro\nDesc $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == -1, "failed to parse rule");

	s = "Action Match\nUser $macro\nDesc $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == -1, "failed to parse rule");


	s = "Action Divert\nUser *\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nUser *\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nUser *\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nUser *\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nUser *\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nUser *\nDesc desc\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nUser *\nDesc desc\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nUser *\nDesc desc\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nUser *\nDesc desc\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nUser *\nDesc desc\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nUser $macro\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nUser $macro\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nUser $macro\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nUser $macro\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nUser $macro\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nUser $macro\nDesc desc\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nUser $macro\nDesc desc\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nUser $macro\nDesc desc\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nUser $macro\nDesc desc\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nUser $macro\nDesc desc\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nUser $macro\nDesc $macro\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nUser $macro\nDesc $macro\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nUser $macro\nDesc $macro\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nUser $macro\nDesc $macro\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nUser $macro\nDesc $macro\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	opts_free(opts);
	conn_opts_free(conn_opts);
	tmp_opts_free(tmp_opts);
}
END_TEST
#endif /* !WITHOUT_USERAUTH */

START_TEST(set_filter_struct_04)
{
	char *s;
	int rv;
	opts_t *opts = opts_new();
	conn_opts_t *conn_opts = conn_opts_new();

	tmp_opts_t *tmp_opts = malloc(sizeof (tmp_opts_t));
	memset(tmp_opts, 0, sizeof (tmp_opts_t));

	FILE *f;
	unsigned int line_num = 0;

	s = "Action Divert\nDstIp *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nDstIp *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nDstIp *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nDstIp *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nDstIp *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nDstIp *\nDstPort *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nDstIp *\nDstPort *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nDstIp *\nDstPort *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nDstIp *\nDstPort *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nDstIp *\nDstPort *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nDstIp 192.168.0.1\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nDstIp 192.168.0.1\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nDstIp 192.168.0.1\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nDstIp 192.168.0.1\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nDstIp 192.168.0.1\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nDstIp 192.168.0.1\nDstPort *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nDstIp 192.168.0.1\nDstPort *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nDstIp 192.168.0.1\nDstPort *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nDstIp 192.168.0.1\nDstPort *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nDstIp 192.168.0.1\nDstPort *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nDstIp *\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nDstIp *\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nDstIp *\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nDstIp *\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nDstIp *\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nDstIp 192.168.0.1\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nDstIp 192.168.0.1\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nDstIp 192.168.0.1\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nDstIp 192.168.0.1\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nDstIp 192.168.0.1\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = strdup("$macro1 192.168.0.1 192.168.0.2 192.168.0.1*");
	rv = filter_macro_set(opts, s, 0);
	fail_unless(rv == 0, "failed to set macro");
	free(s);

	s = strdup("$macro2 443 444 80*");
	rv = filter_macro_set(opts, s, 0);
	fail_unless(rv == 0, "failed to set macro");
	free(s);

	s = "Action Divert\nDstIp $macro1\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nDstIp $macro1\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nDstIp $macro1\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nDstIp $macro1\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nDstIp $macro1\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	opts_free(opts);
	conn_opts_free(conn_opts);
	tmp_opts_free(tmp_opts);
}
END_TEST

START_TEST(set_filter_struct_05)
{
	char *s;
	int rv;
	opts_t *opts = opts_new();
	conn_opts_t *conn_opts = conn_opts_new();

	tmp_opts_t *tmp_opts = malloc(sizeof (tmp_opts_t));
	memset(tmp_opts, 0, sizeof (tmp_opts_t));

	FILE *f;
	unsigned int line_num = 0;

	s = strdup("$macro example.com example*");
	rv = filter_macro_set(opts, s, 0);
	fail_unless(rv == 0, "failed to set macro");
	free(s);

	s = strdup("$macro2 443 444 80*");
	rv = filter_macro_set(opts, s, 0);
	fail_unless(rv == 0, "failed to set macro");
	free(s);


	s = "Action Divert\nSNI *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nSNI *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nSNI *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nSNI *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nSNI *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nSNI example.com\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nSNI example.com\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nSNI example.com\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nSNI example.com\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nSNI example.com\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nSNI example.com\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nSNI example.com\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nSNI example.com\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nSNI example.com\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nSNI example.com\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nSNI $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nSNI $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nSNI $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nSNI $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nSNI $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nSNI example.com\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nSNI example.com\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nSNI example.com\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nSNI example.com\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nSNI example.com\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nSNI $macro\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nSNI $macro\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nSNI $macro\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nSNI $macro\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nSNI $macro\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nCN *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nCN *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nCN *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nCN *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nCN *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nCN example.com\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nCN example.com\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nCN example.com\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nCN example.com\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nCN example.com\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nCN example.com\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nCN example.com\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nCN example.com\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nCN example.com\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nCN example.com\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nCN $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nCN $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nCN $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nCN $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nCN $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nCN example.com\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nCN example.com\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nCN example.com\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nCN example.com\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nCN example.com\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nCN $macro\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nCN $macro\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nCN $macro\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nCN $macro\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nCN $macro\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nHost *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nHost *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nHost *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nHost *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nHost *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nHost example.com\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nHost example.com\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nHost example.com\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nHost example.com\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nHost example.com\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nHost example.com\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nHost example.com\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nHost example.com\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nHost example.com\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nHost example.com\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nHost $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nHost $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nHost $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nHost $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nHost $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nHost example.com\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nHost example.com\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nHost example.com\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nHost example.com\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nHost example.com\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nHost $macro\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nHost $macro\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nHost $macro\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nHost $macro\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nHost $macro\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nURI *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nURI *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nURI *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nURI *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nURI *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nURI example.com\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nURI example.com\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nURI example.com\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nURI example.com\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nURI example.com\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nURI example.com\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nURI example.com\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nURI example.com\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nURI example.com\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nURI example.com\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nURI $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nURI $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nURI $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nURI $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nURI $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nURI example.com\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nURI example.com\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nURI example.com\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nURI example.com\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nURI example.com\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nURI $macro\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nURI $macro\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nURI $macro\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nURI $macro\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nURI $macro\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nDstPort $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	opts_free(opts);
	conn_opts_free(conn_opts);
	tmp_opts_free(tmp_opts);
}
END_TEST

START_TEST(set_filter_struct_06)
{
	char *s;
	int rv;
	opts_t *opts = opts_new();
	conn_opts_t *conn_opts = conn_opts_new();

	tmp_opts_t *tmp_opts = malloc(sizeof (tmp_opts_t));
	memset(tmp_opts, 0, sizeof (tmp_opts_t));

	FILE *f;
	unsigned int line_num = 0;

	s = "Action Divert\nLog *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nLog *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nLog *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nLog *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nLog *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nLog connect\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nLog connect\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nLog connect\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nLog connect\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nLog connect\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nLog master\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nLog master\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nLog master\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nLog master\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nLog master\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nLog cert\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nLog cert\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nLog cert\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nLog cert\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nLog cert\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nLog content\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nLog content\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nLog content\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nLog content\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nLog content\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nLog pcap\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nLog pcap\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nLog pcap\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nLog pcap\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nLog pcap\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nLog mirror\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nLog mirror\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nLog mirror\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nLog mirror\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nLog mirror\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nLog !*\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nLog !*\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nLog !*\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nLog !*\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nLog !*\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nLog !connect\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nLog !connect\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nLog !connect\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nLog !connect\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nLog !connect\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nLog !master\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nLog !master\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nLog !master\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nLog !master\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nLog !master\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nLog !cert\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nLog !cert\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nLog !cert\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nLog !cert\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nLog !cert\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nLog !content\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nLog !content\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nLog !content\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nLog !content\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nLog !content\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nLog !pcap\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nLog !pcap\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nLog !pcap\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nLog !pcap\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nLog !pcap\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = "Action Divert\nLog !mirror\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nLog !mirror\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nLog !mirror\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nLog !mirror\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nLog !mirror\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = strdup("$macro connect master cert content pcap mirror");
	rv = filter_macro_set(opts, s, 0);
	fail_unless(rv == 0, "failed to set macro");
	free(s);

	s = "Action Divert\nLog $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nLog $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nLog $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nLog $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nLog $macro\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = strdup("$macro2 !connect !master !cert !content !pcap !mirror");
	rv = filter_macro_set(opts, s, 0);
	fail_unless(rv == 0, "failed to set macro");
	free(s);

	s = "Action Divert\nLog $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nLog $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nLog $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nLog $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nLog $macro2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = strdup("$macro3 connect !master cert !content pcap !mirror");
	rv = filter_macro_set(opts, s, 0);
	fail_unless(rv == 0, "failed to set macro");
	free(s);

	s = "Action Divert\nLog $macro3\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nLog $macro3\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nLog $macro3\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nLog $macro3\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nLog $macro3\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = strdup("$macro4 !connect master !cert content !pcap mirror");
	rv = filter_macro_set(opts, s, 0);
	fail_unless(rv == 0, "failed to set macro");
	free(s);

	s = "Action Divert\nLog $macro4\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nLog $macro4\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nLog $macro4\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nLog $macro4\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nLog $macro4\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = strdup("$macro5 connect master cert !content !pcap !mirror");
	rv = filter_macro_set(opts, s, 0);
	fail_unless(rv == 0, "failed to set macro");
	free(s);

	s = "Action Divert\nLog $macro5\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nLog $macro5\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nLog $macro5\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nLog $macro5\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nLog $macro5\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");


	s = strdup("$macro6 !connect !master !cert content pcap mirror");
	rv = filter_macro_set(opts, s, 0);
	fail_unless(rv == 0, "failed to set macro");
	free(s);

	s = "Action Divert\nLog $macro6\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nLog $macro6\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nLog $macro6\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nLog $macro6\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nLog $macro6\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	opts_free(opts);
	conn_opts_free(conn_opts);
	tmp_opts_free(tmp_opts);
}
END_TEST

#ifndef WITHOUT_USERAUTH
START_TEST(set_filter_struct_07)
{
	char *s;
	int rv;
	opts_t *opts = opts_new();
	conn_opts_t *conn_opts = conn_opts_new();

	tmp_opts_t *tmp_opts = malloc(sizeof (tmp_opts_t));
	memset(tmp_opts, 0, sizeof (tmp_opts_t));

	FILE *f;
	unsigned int line_num = 0;

	s = "Action Divert\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nSrcIp *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Repeat to add the Pass action as in the filter.t.c tests
	s = "Action Pass\nSrcIp *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nSrcIp *\nDstIp 192.168.0.1\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Block\nUser *\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nDesc *\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nUser *\nDesc desc\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nUser root\nDesc *\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Divert\nUser *\nDesc *\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nLog *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = filter_rule_str(opts->filter_rules);
	fail_unless(!strcmp(s,
		"filter rule 0: site=, port=, ip=, user=, desc=, exact=||||, all=conns||sites|, action=divert||||, log=|||||, apply to=dstip|sni|cn|host|uri, precedence=0\n"
		"filter rule 1: site=, port=, ip=, user=, desc=, exact=||||, all=conns||sites|, action=|split|||, log=|||||, apply to=dstip|sni|cn|host|uri, precedence=0\n"
		"filter rule 2: site=, port=, ip=, user=, desc=, exact=||||, all=conns||sites|, action=||pass||, log=|||||, apply to=dstip|sni|cn|host|uri, precedence=0\n"
		"filter rule 3: site=192.168.0.1, port=, ip=, user=, desc=, exact=site||||, all=conns|||, action=|||block|, log=|||||, apply to=dstip||||, precedence=1\n"
		"filter rule 4: site=, port=, ip=, user=, desc=, exact=||||, all=|users|sites|, action=|||block|, log=|||||, apply to=dstip|sni|cn|host|uri, precedence=1\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 5: site=, port=, ip=, user=, desc=, exact=||||, all=|users|sites|, action=||||match, log=|||||, apply to=dstip|sni|cn|host|uri, precedence=1\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 6: site=, port=, ip=, user=, desc=desc, exact=||||desc, all=|users|sites|, action=|split|||, log=|||||, apply to=dstip|sni|cn|host|uri, precedence=2\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 7: site=, port=, ip=, user=root, desc=, exact=|||user|, all=||sites|, action=||pass||, log=|||||, apply to=dstip|sni|cn|host|uri, precedence=2\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 8: site=, port=, ip=, user=, desc=, exact=||||, all=|users|sites|, action=divert||||, log=|||||, apply to=dstip|sni|cn|host|uri, precedence=1\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 9: site=, port=, ip=, user=, desc=, exact=||||, all=conns||sites|, action=||||match, log=connect|master|cert|content|pcap|mirror, apply to=dstip|sni|cn|host|uri, precedence=1"
		),
		"failed to parse rule: %s", s);
	free(s);

	opts->filter = filter_set(opts->filter_rules, "sslproxy", tmp_opts);
	s = filter_str(opts->filter);

	// check cannot test long strings, so divide s into head and tail
	// Test the tail first, because we will trim the tail to test the head next
	fail_unless(!strcmp(strstr(s, "user_filter_all->\n"),
"user_filter_all->\n"
"    ip all:\n"
"      0:  (all_sites, substring, action=divert|||block|match, log=|||||, precedence=1\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"    sni all:\n"
"      0:  (all_sites, substring, action=divert|||block|match, log=|||||, precedence=1\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"    cn all:\n"
"      0:  (all_sites, substring, action=divert|||block|match, log=|||||, precedence=1\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"    host all:\n"
"      0:  (all_sites, substring, action=divert|||block|match, log=|||||, precedence=1\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"    uri all:\n"
"      0:  (all_sites, substring, action=divert|||block|match, log=|||||, precedence=1\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"ip_filter_exact->\n"
"ip_filter_substring->\n"
"filter_all->\n"
"    ip exact:\n"
"      0: 192.168.0.1 (exact, action=|||block|, log=|||||, precedence=1)\n"
"    ip all:\n"
"      0:  (all_sites, substring, action=divert|split|pass||match, log=connect|master|cert|content|pcap|mirror, precedence=1)\n"
"    sni all:\n"
"      0:  (all_sites, substring, action=divert|split|pass||match, log=connect|master|cert|content|pcap|mirror, precedence=1)\n"
"    cn all:\n"
"      0:  (all_sites, substring, action=divert|split|pass||match, log=connect|master|cert|content|pcap|mirror, precedence=1)\n"
"    host all:\n"
"      0:  (all_sites, substring, action=divert|split|pass||match, log=connect|master|cert|content|pcap|mirror, precedence=1)\n"
"    uri all:\n"
"      0:  (all_sites, substring, action=divert|split|pass||match, log=connect|master|cert|content|pcap|mirror, precedence=1)\n"
		), "failed to translate rule tail: %s", strstr(s, "user_filter_all->\n"));

	// Trim the tail
	char *p = strstr(s, "user_filter_all->\n");
	*p = '\0';

	fail_unless(!strcmp(s, "filter=>\n"
"userdesc_filter_exact->\n"
"userdesc_filter_substring->\n"
"user_filter_exact->\n"
"  user 0 root (exact)=\n"
"    ip all:\n"
"      0:  (all_sites, substring, action=||pass||, log=|||||, precedence=2\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"    sni all:\n"
"      0:  (all_sites, substring, action=||pass||, log=|||||, precedence=2\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"    cn all:\n"
"      0:  (all_sites, substring, action=||pass||, log=|||||, precedence=2\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"    host all:\n"
"      0:  (all_sites, substring, action=||pass||, log=|||||, precedence=2\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"    uri all:\n"
"      0:  (all_sites, substring, action=||pass||, log=|||||, precedence=2\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"user_filter_substring->\n"
"desc_filter_exact->\n"
"   desc 0 desc (exact)=\n"
"    ip all:\n"
"      0:  (all_sites, substring, action=|split|||, log=|||||, precedence=2\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"    sni all:\n"
"      0:  (all_sites, substring, action=|split|||, log=|||||, precedence=2\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"    cn all:\n"
"      0:  (all_sites, substring, action=|split|||, log=|||||, precedence=2\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"    host all:\n"
"      0:  (all_sites, substring, action=|split|||, log=|||||, precedence=2\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"    uri all:\n"
"      0:  (all_sites, substring, action=|split|||, log=|||||, precedence=2\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"desc_filter_substring->\n"
		), "failed to translate rule head: %s", s);

	free(s);

	opts_free(opts);
	conn_opts_free(conn_opts);
	tmp_opts_free(tmp_opts);
}
END_TEST
#endif /* !WITHOUT_USERAUTH */

START_TEST(set_filter_struct_08)
{
	char *s;
	int rv;
	opts_t *opts = opts_new();
	conn_opts_t *conn_opts = conn_opts_new();

	tmp_opts_t *tmp_opts = malloc(sizeof (tmp_opts_t));
	memset(tmp_opts, 0, sizeof (tmp_opts_t));

	FILE *f;
	unsigned int line_num = 0;

	s = "Action Divert\nSrcIp 192.168.0.1\nDstIp 192.168.0.2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nSrcIp 192.168.0.1\nDstIp 192.168.0.2\nLog connect master cert content pcap mirror\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nSrcIp 192.168.0.1\nDstIp 192.168.0.2\nLog !connect !cert !pcap\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Block action at precedence 1 is not applied to a site of the same rule at precedence 2 now
	s = "Action Block\nSrcIp 192.168.0.1\nDstIp 192.168.0.2\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Add another target
	s = "Action Match\nSrcIp 192.168.0.1\nDstIp 192.168.0.3\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Add another source
	s = "Action Match\nSrcIp 192.168.0.2\nDstIp 192.168.0.1\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nSrcIp 192.168.0.2\nDstIp *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Search substring (subnet?)
	s = "Action Match\nSrcIp 192.168.0.2\nDstIp 192.168.0.*\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Add another target
	s = "Action Match\nSrcIp 192.168.0.2\nDstIp 192.168.0.3\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Add substring src
	s = "Action Match\nSrcIp 192.168.1.*\nDstIp 192.168.0.1\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Add substring src and target
	s = "Action Match\nSrcIp 192.168.2.*\nDstIp 192.168.3.*\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = filter_rule_str(opts->filter_rules);
#ifndef WITHOUT_USERAUTH
	fail_unless(!strcmp(s,
		"filter rule 0: site=192.168.0.2, port=, ip=192.168.0.1, user=, desc=, exact=site||ip||, all=|||, action=divert||||, log=|||||, apply to=dstip||||, precedence=2\n"
		"filter rule 1: site=192.168.0.2, port=, ip=192.168.0.1, user=, desc=, exact=site||ip||, all=|||, action=|split|||, log=connect|master|cert|content|pcap|mirror, apply to=dstip||||, precedence=3\n"
		"filter rule 2: site=192.168.0.2, port=, ip=192.168.0.1, user=, desc=, exact=site||ip||, all=|||, action=||pass||, log=!connect||!cert||!pcap|, apply to=dstip||||, precedence=3\n"
		"filter rule 3: site=192.168.0.2, port=, ip=192.168.0.1, user=, desc=, exact=site||ip||, all=|||, action=|||block|, log=|||||, apply to=dstip||||, precedence=2\n"
		"filter rule 4: site=192.168.0.3, port=, ip=192.168.0.1, user=, desc=, exact=site||ip||, all=|||, action=||||match, log=|||||, apply to=dstip||||, precedence=2\n"
		"filter rule 5: site=192.168.0.1, port=, ip=192.168.0.2, user=, desc=, exact=site||ip||, all=|||, action=||||match, log=|||||, apply to=dstip||||, precedence=2\n"
		"filter rule 6: site=, port=, ip=192.168.0.2, user=, desc=, exact=||ip||, all=||sites|, action=||||match, log=|||||, apply to=dstip||||, precedence=2\n"
		"filter rule 7: site=192.168.0., port=, ip=192.168.0.2, user=, desc=, exact=||ip||, all=|||, action=||||match, log=|||||, apply to=dstip||||, precedence=2\n"
		"filter rule 8: site=192.168.0.3, port=, ip=192.168.0.2, user=, desc=, exact=site||ip||, all=|||, action=||||match, log=|||||, apply to=dstip||||, precedence=2\n"
		"filter rule 9: site=192.168.0.1, port=, ip=192.168.1., user=, desc=, exact=site||||, all=|||, action=||||match, log=|||||, apply to=dstip||||, precedence=2\n"
		"filter rule 10: site=192.168.3., port=, ip=192.168.2., user=, desc=, exact=||||, all=|||, action=||||match, log=|||||, apply to=dstip||||, precedence=2"),
		"failed to parse rule: %s", s);
#else /* WITHOUT_USERAUTH */
	fail_unless(!strcmp(s,
		"filter rule 0: site=192.168.0.2, port=, ip=192.168.0.1, exact=site||ip, all=||, action=divert||||, log=|||||, apply to=dstip||||, precedence=2\n"
		"filter rule 1: site=192.168.0.2, port=, ip=192.168.0.1, exact=site||ip, all=||, action=|split|||, log=connect|master|cert|content|pcap|mirror, apply to=dstip||||, precedence=3\n"
		"filter rule 2: site=192.168.0.2, port=, ip=192.168.0.1, exact=site||ip, all=||, action=||pass||, log=!connect||!cert||!pcap|, apply to=dstip||||, precedence=3\n"
		"filter rule 3: site=192.168.0.2, port=, ip=192.168.0.1, exact=site||ip, all=||, action=|||block|, log=|||||, apply to=dstip||||, precedence=2\n"
		"filter rule 4: site=192.168.0.3, port=, ip=192.168.0.1, exact=site||ip, all=||, action=||||match, log=|||||, apply to=dstip||||, precedence=2\n"
		"filter rule 5: site=192.168.0.1, port=, ip=192.168.0.2, exact=site||ip, all=||, action=||||match, log=|||||, apply to=dstip||||, precedence=2\n"
		"filter rule 6: site=, port=, ip=192.168.0.2, exact=||ip, all=|sites|, action=||||match, log=|||||, apply to=dstip||||, precedence=2\n"
		"filter rule 7: site=192.168.0., port=, ip=192.168.0.2, exact=||ip, all=||, action=||||match, log=|||||, apply to=dstip||||, precedence=2\n"
		"filter rule 8: site=192.168.0.3, port=, ip=192.168.0.2, exact=site||ip, all=||, action=||||match, log=|||||, apply to=dstip||||, precedence=2\n"
		"filter rule 9: site=192.168.0.1, port=, ip=192.168.1., exact=site||, all=||, action=||||match, log=|||||, apply to=dstip||||, precedence=2\n"
		"filter rule 10: site=192.168.3., port=, ip=192.168.2., exact=||, all=||, action=||||match, log=|||||, apply to=dstip||||, precedence=2"),
		"failed to parse rule: %s", s);
#endif /* WITHOUT_USERAUTH */
	free(s);

	opts->filter = filter_set(opts->filter_rules, "sslproxy", tmp_opts);

	s = filter_str(opts->filter);
#ifndef WITHOUT_USERAUTH
	fail_unless(!strcmp(s, "filter=>\n"
"userdesc_filter_exact->\n"
"userdesc_filter_substring->\n"
"user_filter_exact->\n"
"user_filter_substring->\n"
"desc_filter_exact->\n"
"desc_filter_substring->\n"
"user_filter_all->\n"
"ip_filter_exact->\n"
"  ip 0 192.168.0.1 (exact)=\n"
"    ip exact:\n"
"      0: 192.168.0.2 (exact, action=divert|split|pass||, log=!connect|master|!cert|content|!pcap|mirror, precedence=3)\n"
"      1: 192.168.0.3 (exact, action=||||match, log=|||||, precedence=2)\n"
"  ip 1 192.168.0.2 (exact)=\n"
"    ip exact:\n"
"      0: 192.168.0.1 (exact, action=||||match, log=|||||, precedence=2)\n"
"      1: 192.168.0.3 (exact, action=||||match, log=|||||, precedence=2)\n"
"    ip substring:\n"
"      0: 192.168.0. (substring, action=||||match, log=|||||, precedence=2)\n"
"    ip all:\n"
"      0:  (all_sites, substring, action=||||match, log=|||||, precedence=2)\n"
"ip_filter_substring->\n"
"  ip 0 192.168.1. (substring)=\n"
"    ip exact:\n"
"      0: 192.168.0.1 (exact, action=||||match, log=|||||, precedence=2)\n"
"  ip 1 192.168.2. (substring)=\n"
"    ip substring:\n"
"      0: 192.168.3. (substring, action=||||match, log=|||||, precedence=2)\n"
"filter_all->\n"), "failed to translate rule: %s", s);
#else /* WITHOUT_USERAUTH */
	fail_unless(!strcmp(s, "filter=>\n"
"ip_filter_exact->\n"
"  ip 0 192.168.0.1 (exact)=\n"
"    ip exact:\n"
"      0: 192.168.0.2 (exact, action=divert|split|pass||, log=!connect|master|!cert|content|!pcap|mirror, precedence=3)\n"
"      1: 192.168.0.3 (exact, action=||||match, log=|||||, precedence=2)\n"
"  ip 1 192.168.0.2 (exact)=\n"
"    ip exact:\n"
"      0: 192.168.0.1 (exact, action=||||match, log=|||||, precedence=2)\n"
"      1: 192.168.0.3 (exact, action=||||match, log=|||||, precedence=2)\n"
"    ip substring:\n"
"      0: 192.168.0. (substring, action=||||match, log=|||||, precedence=2)\n"
"    ip all:\n"
"      0:  (all_sites, substring, action=||||match, log=|||||, precedence=2)\n"
"ip_filter_substring->\n"
"  ip 0 192.168.1. (substring)=\n"
"    ip exact:\n"
"      0: 192.168.0.1 (exact, action=||||match, log=|||||, precedence=2)\n"
"  ip 1 192.168.2. (substring)=\n"
"    ip substring:\n"
"      0: 192.168.3. (substring, action=||||match, log=|||||, precedence=2)\n"
"filter_all->\n"), "failed to translate rule: %s", s);
#endif /* WITHOUT_USERAUTH */
	free(s);

	opts_free(opts);
	conn_opts_free(conn_opts);
	tmp_opts_free(tmp_opts);
}
END_TEST

START_TEST(set_filter_struct_09)
{
	char *s;
	int rv;
	opts_t *opts = opts_new();
	conn_opts_t *conn_opts = conn_opts_new();

	tmp_opts_t *tmp_opts = malloc(sizeof (tmp_opts_t));
	memset(tmp_opts, 0, sizeof (tmp_opts_t));

	FILE *f;
	unsigned int line_num = 0;

	s = "Action Divert\nSrcIp 192.168.0.1\nDstIp 192.168.0.2\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nSrcIp 192.168.0.1\nDstIp 192.168.0.2\nDstPort 443\nLog connect master cert content pcap mirror\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nSrcIp 192.168.0.1\nDstIp 192.168.0.2\nDstPort 443\nLog !connect !cert !pcap\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Block action at precedence 2 is not applied to a port of the same rule at precedence 3 now
	s = "Action Block\nSrcIp 192.168.0.1\nDstIp 192.168.0.2\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Add another target, the following port rules should not change this site rule
	s = "Action Match\nSrcIp 192.168.0.1\nDstIp 192.168.0.3\nLog !mirror\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Add another target port
	s = "Action Match\nSrcIp 192.168.0.1\nDstIp 192.168.0.3\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Add another target port
	s = "Action Match\nSrcIp 192.168.0.1\nDstIp 192.168.0.3\nDstPort 80\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Add another source
	s = "Action Match\nSrcIp 192.168.0.2\nDstIp 192.168.0.1\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Add substring source
	s = "Action Match\nSrcIp 192.168.1.*\nDstIp 192.168.0.1\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Add substring source and target
	s = "Action Match\nSrcIp 192.168.2.*\nDstIp 192.168.3.*\nDstPort 443\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nSrcIp 192.168.0.2\nDstIp 192.168.0.1\nDstPort *\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Search substring
	s = "Action Match\nSrcIp 192.168.0.2\nDstIp 192.168.0.1\nDstPort 80*\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Add substring source, target, and port
	s = "Action Match\nSrcIp 192.168.4.*\nDstIp 192.168.5.*\nDstPort 80*\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = filter_rule_str(opts->filter_rules);
#ifndef WITHOUT_USERAUTH
	fail_unless(!strcmp(s,
		"filter rule 0: site=192.168.0.2, port=443, ip=192.168.0.1, user=, desc=, exact=site|port|ip||, all=|||, action=divert||||, log=|||||, apply to=dstip||||, precedence=3\n"
		"filter rule 1: site=192.168.0.2, port=443, ip=192.168.0.1, user=, desc=, exact=site|port|ip||, all=|||, action=|split|||, log=connect|master|cert|content|pcap|mirror, apply to=dstip||||, precedence=4\n"
		"filter rule 2: site=192.168.0.2, port=443, ip=192.168.0.1, user=, desc=, exact=site|port|ip||, all=|||, action=||pass||, log=!connect||!cert||!pcap|, apply to=dstip||||, precedence=4\n"
		"filter rule 3: site=192.168.0.2, port=443, ip=192.168.0.1, user=, desc=, exact=site|port|ip||, all=|||, action=|||block|, log=|||||, apply to=dstip||||, precedence=3\n"
		"filter rule 4: site=192.168.0.3, port=, ip=192.168.0.1, user=, desc=, exact=site||ip||, all=|||, action=||||match, log=|||||!mirror, apply to=dstip||||, precedence=3\n"
		"filter rule 5: site=192.168.0.3, port=443, ip=192.168.0.1, user=, desc=, exact=site|port|ip||, all=|||, action=||||match, log=|||||, apply to=dstip||||, precedence=3\n"
		"filter rule 6: site=192.168.0.3, port=80, ip=192.168.0.1, user=, desc=, exact=site|port|ip||, all=|||, action=||||match, log=|||||, apply to=dstip||||, precedence=3\n"
		"filter rule 7: site=192.168.0.1, port=443, ip=192.168.0.2, user=, desc=, exact=site|port|ip||, all=|||, action=||||match, log=|||||, apply to=dstip||||, precedence=3\n"
		"filter rule 8: site=192.168.0.1, port=443, ip=192.168.1., user=, desc=, exact=site|port|||, all=|||, action=||||match, log=|||||, apply to=dstip||||, precedence=3\n"
		"filter rule 9: site=192.168.3., port=443, ip=192.168.2., user=, desc=, exact=|port|||, all=|||, action=||||match, log=|||||, apply to=dstip||||, precedence=3\n"
		"filter rule 10: site=192.168.0.1, port=, ip=192.168.0.2, user=, desc=, exact=site||ip||, all=|||ports, action=||||match, log=|||||, apply to=dstip||||, precedence=3\n"
		"filter rule 11: site=192.168.0.1, port=80, ip=192.168.0.2, user=, desc=, exact=site||ip||, all=|||, action=||||match, log=|||||, apply to=dstip||||, precedence=3\n"
		"filter rule 12: site=192.168.5., port=80, ip=192.168.4., user=, desc=, exact=||||, all=|||, action=||||match, log=|||||, apply to=dstip||||, precedence=3"),
		"failed to parse rule: %s", s);
#else /* WITHOUT_USERAUTH */
	fail_unless(!strcmp(s,
		"filter rule 0: site=192.168.0.2, port=443, ip=192.168.0.1, exact=site|port|ip, all=||, action=divert||||, log=|||||, apply to=dstip||||, precedence=3\n"
		"filter rule 1: site=192.168.0.2, port=443, ip=192.168.0.1, exact=site|port|ip, all=||, action=|split|||, log=connect|master|cert|content|pcap|mirror, apply to=dstip||||, precedence=4\n"
		"filter rule 2: site=192.168.0.2, port=443, ip=192.168.0.1, exact=site|port|ip, all=||, action=||pass||, log=!connect||!cert||!pcap|, apply to=dstip||||, precedence=4\n"
		"filter rule 3: site=192.168.0.2, port=443, ip=192.168.0.1, exact=site|port|ip, all=||, action=|||block|, log=|||||, apply to=dstip||||, precedence=3\n"
		"filter rule 4: site=192.168.0.3, port=, ip=192.168.0.1, exact=site||ip, all=||, action=||||match, log=|||||!mirror, apply to=dstip||||, precedence=3\n"
		"filter rule 5: site=192.168.0.3, port=443, ip=192.168.0.1, exact=site|port|ip, all=||, action=||||match, log=|||||, apply to=dstip||||, precedence=3\n"
		"filter rule 6: site=192.168.0.3, port=80, ip=192.168.0.1, exact=site|port|ip, all=||, action=||||match, log=|||||, apply to=dstip||||, precedence=3\n"
		"filter rule 7: site=192.168.0.1, port=443, ip=192.168.0.2, exact=site|port|ip, all=||, action=||||match, log=|||||, apply to=dstip||||, precedence=3\n"
		"filter rule 8: site=192.168.0.1, port=443, ip=192.168.1., exact=site|port|, all=||, action=||||match, log=|||||, apply to=dstip||||, precedence=3\n"
		"filter rule 9: site=192.168.3., port=443, ip=192.168.2., exact=|port|, all=||, action=||||match, log=|||||, apply to=dstip||||, precedence=3\n"
		"filter rule 10: site=192.168.0.1, port=, ip=192.168.0.2, exact=site||ip, all=||ports, action=||||match, log=|||||, apply to=dstip||||, precedence=3\n"
		"filter rule 11: site=192.168.0.1, port=80, ip=192.168.0.2, exact=site||ip, all=||, action=||||match, log=|||||, apply to=dstip||||, precedence=3\n"
		"filter rule 12: site=192.168.5., port=80, ip=192.168.4., exact=||, all=||, action=||||match, log=|||||, apply to=dstip||||, precedence=3"),
		"failed to parse rule: %s", s);
#endif /* WITHOUT_USERAUTH */
	free(s);

	opts->filter = filter_set(opts->filter_rules, "sslproxy", tmp_opts);

	s = filter_str(opts->filter);
#ifndef WITHOUT_USERAUTH
	fail_unless(!strcmp(s, "filter=>\n"
"userdesc_filter_exact->\n"
"userdesc_filter_substring->\n"
"user_filter_exact->\n"
"user_filter_substring->\n"
"desc_filter_exact->\n"
"desc_filter_substring->\n"
"user_filter_all->\n"
"ip_filter_exact->\n"
"  ip 0 192.168.0.1 (exact)=\n"
"    ip exact:\n"
"      0: 192.168.0.2 (exact, action=||||, log=|||||, precedence=0)\n"
"        port exact:\n"
"          0: 443 (exact, action=divert|split|pass||, log=!connect|master|!cert|content|!pcap|mirror, precedence=4)\n"
"      1: 192.168.0.3 (exact, action=||||match, log=|||||!mirror, precedence=3)\n"
"        port exact:\n"
"          0: 443 (exact, action=||||match, log=|||||, precedence=3)\n"
"          1: 80 (exact, action=||||match, log=|||||, precedence=3)\n"
"  ip 1 192.168.0.2 (exact)=\n"
"    ip exact:\n"
"      0: 192.168.0.1 (exact, action=||||, log=|||||, precedence=0)\n"
"        port exact:\n"
"          0: 443 (exact, action=||||match, log=|||||, precedence=3)\n"
"        port substring:\n"
"          0: 80 (substring, action=||||match, log=|||||, precedence=3)\n"
"        port all:\n"
"          0:  (all_ports, substring, action=||||match, log=|||||, precedence=3)\n"
"ip_filter_substring->\n"
"  ip 0 192.168.1. (substring)=\n"
"    ip exact:\n"
"      0: 192.168.0.1 (exact, action=||||, log=|||||, precedence=0)\n"
"        port exact:\n"
"          0: 443 (exact, action=||||match, log=|||||, precedence=3)\n"
"  ip 1 192.168.2. (substring)=\n"
"    ip substring:\n"
"      0: 192.168.3. (substring, action=||||, log=|||||, precedence=0)\n"
"        port exact:\n"
"          0: 443 (exact, action=||||match, log=|||||, precedence=3)\n"
"  ip 2 192.168.4. (substring)=\n"
"    ip substring:\n"
"      0: 192.168.5. (substring, action=||||, log=|||||, precedence=0)\n"
"        port substring:\n"
"          0: 80 (substring, action=||||match, log=|||||, precedence=3)\n"
"filter_all->\n"), "failed to translate rule: %s", s);
#else /* WITHOUT_USERAUTH */
	fail_unless(!strcmp(s, "filter=>\n"
"ip_filter_exact->\n"
"  ip 0 192.168.0.1 (exact)=\n"
"    ip exact:\n"
"      0: 192.168.0.2 (exact, action=||||, log=|||||, precedence=0)\n"
"        port exact:\n"
"          0: 443 (exact, action=divert|split|pass||, log=!connect|master|!cert|content|!pcap|mirror, precedence=4)\n"
"      1: 192.168.0.3 (exact, action=||||match, log=|||||!mirror, precedence=3)\n"
"        port exact:\n"
"          0: 443 (exact, action=||||match, log=|||||, precedence=3)\n"
"          1: 80 (exact, action=||||match, log=|||||, precedence=3)\n"
"  ip 1 192.168.0.2 (exact)=\n"
"    ip exact:\n"
"      0: 192.168.0.1 (exact, action=||||, log=|||||, precedence=0)\n"
"        port exact:\n"
"          0: 443 (exact, action=||||match, log=|||||, precedence=3)\n"
"        port substring:\n"
"          0: 80 (substring, action=||||match, log=|||||, precedence=3)\n"
"        port all:\n"
"          0:  (all_ports, substring, action=||||match, log=|||||, precedence=3)\n"
"ip_filter_substring->\n"
"  ip 0 192.168.1. (substring)=\n"
"    ip exact:\n"
"      0: 192.168.0.1 (exact, action=||||, log=|||||, precedence=0)\n"
"        port exact:\n"
"          0: 443 (exact, action=||||match, log=|||||, precedence=3)\n"
"  ip 1 192.168.2. (substring)=\n"
"    ip substring:\n"
"      0: 192.168.3. (substring, action=||||, log=|||||, precedence=0)\n"
"        port exact:\n"
"          0: 443 (exact, action=||||match, log=|||||, precedence=3)\n"
"  ip 2 192.168.4. (substring)=\n"
"    ip substring:\n"
"      0: 192.168.5. (substring, action=||||, log=|||||, precedence=0)\n"
"        port substring:\n"
"          0: 80 (substring, action=||||match, log=|||||, precedence=3)\n"
"filter_all->\n"), "failed to translate rule: %s", s);
#endif /* WITHOUT_USERAUTH */
	free(s);

	opts_free(opts);
	conn_opts_free(conn_opts);
	tmp_opts_free(tmp_opts);
}
END_TEST

#ifndef WITHOUT_USERAUTH
START_TEST(set_filter_struct_10)
{
	char *s;
	int rv;
	opts_t *opts = opts_new();
	conn_opts_t *conn_opts = conn_opts_new();

	tmp_opts_t *tmp_opts = malloc(sizeof (tmp_opts_t));
	memset(tmp_opts, 0, sizeof (tmp_opts_t));

	FILE *f;
	unsigned int line_num = 0;

	s = "Action Divert\nUser root\nSNI example.com\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nUser root\nSNI example.com\nLog connect master cert content pcap mirror\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Move UserAuth up once at each new rule
	s = "Action Pass\nUser root\nSNI example.com\nUserAuth yes\nLog !connect !cert !pcap\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Block action at precedence 2 is not applied to a site of the same rule at precedence 4 now
	s = "Action Block\nUser root\nUserAuth yes\nSNI example.com\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Add another target
	s = "Action Match\nUserAuth yes\nUser root\nSNI example2.com\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Add another source
	s = "UserAuth yes\nAction Match\nUser daemon\nSNI example.com\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nUser daemon\nSNI *\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Search substring (subdomain?)
	s = "Action Match\nUser daemon\nSNI .example.com*\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Add another target
	s = "Action Match\nUser daemon\nSNI example3.com\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Add substring source
	s = "Action Match\nUser admin1*\nSNI example4.com\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nUser admin2*\nSNI example5.com\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = filter_rule_str(opts->filter_rules);
	fail_unless(!strcmp(s,
		"filter rule 0: site=example.com, port=, ip=, user=root, desc=, exact=site|||user|, all=|||, action=divert||||, log=|||||, apply to=|sni|||, precedence=3\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 1: site=example.com, port=, ip=, user=root, desc=, exact=site|||user|, all=|||, action=|split|||, log=connect|master|cert|content|pcap|mirror, apply to=|sni|||, precedence=4\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 2: site=example.com, port=, ip=, user=root, desc=, exact=site|||user|, all=|||, action=||pass||, log=!connect||!cert||!pcap|, apply to=|sni|||, precedence=4\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 3: site=example.com, port=, ip=, user=root, desc=, exact=site|||user|, all=|||, action=|||block|, log=|||||, apply to=|sni|||, precedence=3\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 4: site=example2.com, port=, ip=, user=root, desc=, exact=site|||user|, all=|||, action=||||match, log=|||||, apply to=|sni|||, precedence=3\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 5: site=example.com, port=, ip=, user=daemon, desc=, exact=site|||user|, all=|||, action=||||match, log=|||||, apply to=|sni|||, precedence=3\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 6: site=, port=, ip=, user=daemon, desc=, exact=|||user|, all=||sites|, action=||||match, log=|||||, apply to=|sni|||, precedence=3\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 7: site=.example.com, port=, ip=, user=daemon, desc=, exact=|||user|, all=|||, action=||||match, log=|||||, apply to=|sni|||, precedence=3\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 8: site=example3.com, port=, ip=, user=daemon, desc=, exact=site|||user|, all=|||, action=||||match, log=|||||, apply to=|sni|||, precedence=3\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 9: site=example4.com, port=, ip=, user=admin1, desc=, exact=site||||, all=|||, action=||||match, log=|||||, apply to=|sni|||, precedence=3\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 10: site=example5.com, port=, ip=, user=admin2, desc=, exact=site||||, all=|||, action=||||match, log=|||||, apply to=|sni|||, precedence=3\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192"),
		"failed to parse rule: %s", s);
	free(s);

	opts->filter = filter_set(opts->filter_rules, "sslproxy", tmp_opts);

	s = filter_str(opts->filter);
	fail_unless(!strcmp(s, "filter=>\n"
"userdesc_filter_exact->\n"
"userdesc_filter_substring->\n"
"user_filter_exact->\n"
"  user 0 daemon (exact)=\n"
"    sni exact:\n"
"      0: example.com (exact, action=||||match, log=|||||, precedence=3\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"      1: example3.com (exact, action=||||match, log=|||||, precedence=3\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"    sni substring:\n"
"      0: .example.com (substring, action=||||match, log=|||||, precedence=3\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"    sni all:\n"
"      0:  (all_sites, substring, action=||||match, log=|||||, precedence=3\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"  user 1 root (exact)=\n"
"    sni exact:\n"
"      0: example.com (exact, action=divert|split|pass||, log=!connect|master|!cert|content|!pcap|mirror, precedence=4\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"      1: example2.com (exact, action=||||match, log=|||||, precedence=3\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"user_filter_substring->\n"
"  user 0 admin1 (substring)=\n"
"    sni exact:\n"
"      0: example4.com (exact, action=||||match, log=|||||, precedence=3\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"  user 1 admin2 (substring)=\n"
"    sni exact:\n"
"      0: example5.com (exact, action=||||match, log=|||||, precedence=3\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"desc_filter_exact->\n"
"desc_filter_substring->\n"
"user_filter_all->\n"
"ip_filter_exact->\n"
"ip_filter_substring->\n"
"filter_all->\n"), "failed to translate rule: %s", s);
	free(s);

	opts_free(opts);
	conn_opts_free(conn_opts);
	tmp_opts_free(tmp_opts);
}
END_TEST

START_TEST(set_filter_struct_11)
{
	char *s;
	int rv;
	opts_t *opts = opts_new();
	conn_opts_t *conn_opts = conn_opts_new();

	tmp_opts_t *tmp_opts = malloc(sizeof (tmp_opts_t));
	memset(tmp_opts, 0, sizeof (tmp_opts_t));

	FILE *f;
	unsigned int line_num = 0;

	s = "Action Divert\nUser root\nCN example.com\nDstPort 443\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nUser root\nCN example.com\nDstPort 443\nUserAuth yes\nLog connect master cert content pcap mirror\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nUser root\nCN example.com\nDstPort 443\nUserAuth yes\nLog !connect !cert !pcap\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Block action at precedence 3 is not applied to a site of the same rule at precedence 5 now
	s = "Action Block\nUser root\nCN example.com\nDstPort 443\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Add another target
	s = "Action Match\nUser root\nCN example2.com\nDstPort 443\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Add another source
	s = "Action Match\nUser daemon\nCN example.com\nDstPort 443\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nUser daemon\nCN *\nDstPort 443\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nUser daemon\nCN example.com\nDstPort *\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nUser daemon\nCN *\nDstPort *\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Search substring (subdomain?)
	s = "Action Match\nUser daemon\nCN .example.com*\nDstPort 443\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nUser daemon\nCN .example.com*\nDstPort 443*\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Add another target
	s = "Action Match\nUser daemon\nCN example3.com\nDstPort 443\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Add substring source
	s = "Action Match\nUser admin1*\nCN example4.com\nDstPort 443\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nUser admin2*\nCN example5.com\nDstPort 443\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = filter_rule_str(opts->filter_rules);

	fail_unless(!strcmp(strstr(s, "filter rule 7: "),
		"filter rule 7: site=example.com, port=, ip=, user=daemon, desc=, exact=site|||user|, all=|||ports, action=||||match, log=|||||, apply to=||cn||, precedence=4\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 8: site=, port=, ip=, user=daemon, desc=, exact=|||user|, all=||sites|ports, action=||||match, log=|||||, apply to=||cn||, precedence=4\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 9: site=.example.com, port=443, ip=, user=daemon, desc=, exact=|port||user|, all=|||, action=||||match, log=|||||, apply to=||cn||, precedence=4\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 10: site=.example.com, port=443, ip=, user=daemon, desc=, exact=|||user|, all=|||, action=||||match, log=|||||, apply to=||cn||, precedence=4\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 11: site=example3.com, port=443, ip=, user=daemon, desc=, exact=site|port||user|, all=|||, action=||||match, log=|||||, apply to=||cn||, precedence=4\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 12: site=example4.com, port=443, ip=, user=admin1, desc=, exact=site|port|||, all=|||, action=||||match, log=|||||, apply to=||cn||, precedence=4\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 13: site=example5.com, port=443, ip=, user=admin2, desc=, exact=site|port|||, all=|||, action=||||match, log=|||||, apply to=||cn||, precedence=4\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192"),
		"failed to parse rule tail: %s", strstr(s, "filter rule 7: "));

	// Trim the tail
	char *p = strstr(s, "filter rule 7: ");
	*p = '\0';

	fail_unless(!strcmp(s,
		"filter rule 0: site=example.com, port=443, ip=, user=root, desc=, exact=site|port||user|, all=|||, action=divert||||, log=|||||, apply to=||cn||, precedence=4\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 1: site=example.com, port=443, ip=, user=root, desc=, exact=site|port||user|, all=|||, action=|split|||, log=connect|master|cert|content|pcap|mirror, apply to=||cn||, precedence=5\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 2: site=example.com, port=443, ip=, user=root, desc=, exact=site|port||user|, all=|||, action=||pass||, log=!connect||!cert||!pcap|, apply to=||cn||, precedence=5\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 3: site=example.com, port=443, ip=, user=root, desc=, exact=site|port||user|, all=|||, action=|||block|, log=|||||, apply to=||cn||, precedence=4\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 4: site=example2.com, port=443, ip=, user=root, desc=, exact=site|port||user|, all=|||, action=||||match, log=|||||, apply to=||cn||, precedence=4\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 5: site=example.com, port=443, ip=, user=daemon, desc=, exact=site|port||user|, all=|||, action=||||match, log=|||||, apply to=||cn||, precedence=4\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 6: site=, port=443, ip=, user=daemon, desc=, exact=|port||user|, all=||sites|, action=||||match, log=|||||, apply to=||cn||, precedence=4\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"),
		"failed to parse rule head: %s", s);
	free(s);

	opts->filter = filter_set(opts->filter_rules, "sslproxy", tmp_opts);

	s = filter_str(opts->filter);

	fail_unless(!strcmp(strstr(s, "user_filter_substring->\n"),
"user_filter_substring->\n"
"  user 0 admin1 (substring)=\n"
"    cn exact:\n"
"      0: example4.com (exact, action=||||, log=|||||, precedence=0)\n"
"        port exact:\n"
"          0: 443 (exact, action=||||match, log=|||||, precedence=4\n"
"            conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"  user 1 admin2 (substring)=\n"
"    cn exact:\n"
"      0: example5.com (exact, action=||||, log=|||||, precedence=0)\n"
"        port exact:\n"
"          0: 443 (exact, action=||||match, log=|||||, precedence=4\n"
"            conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"desc_filter_exact->\n"
"desc_filter_substring->\n"
"user_filter_all->\n"
"ip_filter_exact->\n"
"ip_filter_substring->\n"
"filter_all->\n"), "failed to translate rule tail: %s", strstr(s, "user_filter_substring->\n"));

	// Trim the tail
	p = strstr(s, "user_filter_substring->\n");
	*p = '\0';

	fail_unless(!strcmp(s, "filter=>\n"
"userdesc_filter_exact->\n"
"userdesc_filter_substring->\n"
"user_filter_exact->\n"
"  user 0 daemon (exact)=\n"
"    cn exact:\n"
"      0: example.com (exact, action=||||, log=|||||, precedence=0)\n"
"        port exact:\n"
"          0: 443 (exact, action=||||match, log=|||||, precedence=4\n"
"            conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"        port all:\n"
"          0:  (all_ports, substring, action=||||match, log=|||||, precedence=4\n"
"            conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"      1: example3.com (exact, action=||||, log=|||||, precedence=0)\n"
"        port exact:\n"
"          0: 443 (exact, action=||||match, log=|||||, precedence=4\n"
"            conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"    cn substring:\n"
"      0: .example.com (substring, action=||||, log=|||||, precedence=0)\n"
"        port exact:\n"
"          0: 443 (exact, action=||||match, log=|||||, precedence=4\n"
"            conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"        port substring:\n"
"          0: 443 (substring, action=||||match, log=|||||, precedence=4\n"
"            conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"    cn all:\n"
"      0:  (all_sites, substring, action=||||, log=|||||, precedence=0)\n"
"        port exact:\n"
"          0: 443 (exact, action=||||match, log=|||||, precedence=4\n"
"            conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"        port all:\n"
"          0:  (all_ports, substring, action=||||match, log=|||||, precedence=4\n"
"            conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"  user 1 root (exact)=\n"
"    cn exact:\n"
"      0: example.com (exact, action=||||, log=|||||, precedence=0)\n"
"        port exact:\n"
"          0: 443 (exact, action=divert|split|pass||, log=!connect|master|!cert|content|!pcap|mirror, precedence=5\n"
"            conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"      1: example2.com (exact, action=||||, log=|||||, precedence=0)\n"
"        port exact:\n"
"          0: 443 (exact, action=||||match, log=|||||, precedence=4\n"
"            conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
			), "failed to translate rule head: %s", s);

	free(s);

	opts_free(opts);
	conn_opts_free(conn_opts);
	tmp_opts_free(tmp_opts);
}
END_TEST

START_TEST(set_filter_struct_12)
{
	char *s;
	int rv;
	opts_t *opts = opts_new();
	conn_opts_t *conn_opts = conn_opts_new();

	tmp_opts_t *tmp_opts = malloc(sizeof (tmp_opts_t));
	memset(tmp_opts, 0, sizeof (tmp_opts_t));

	FILE *f;
	unsigned int line_num = 0;

	s = "Action Divert\nUser root\nDesc desc\nHost example.com\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Split\nUser root\nDesc desc\nHost example.com\nDstPort 443\nLog connect master cert content pcap mirror\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Pass\nUser root\nDesc desc\nHost example.com\nLog !connect !cert !pcap\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Block action at precedence 2 is not applied to a site of the same rule at precedence 5 now
	s = "Action Block\nUser root\nDesc desc\nHost example.com\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Add another target
	s = "Action Match\nUser root\nDesc desc\nHost example2.com\nDstPort 443\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Add another source
	s = "Action Match\nUser daemon\nDesc desc\nHost example.com\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nUser daemon\nDesc desc\nHost *\nDstPort 443\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Search substring (subdomain?)
	s = "Action Match\nUser daemon\nDesc desc\nHost .example.com*\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Add another target
	s = "Action Match\nUser daemon\nDesc desc\nHost example3.com\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Add substring source
	s = "Action Match\nUser admin1*\nDesc desc1*\nHost example4.com\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nUser admin2*\nDesc desc2*\nHost example5.com\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Add another desc
	s = "Action Match\nUser daemon\nDesc desc2\nHost example6.com\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Add all users
	s = "Action Match\nUser *\nDesc desc\nHost example7.com\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Add all users all sni sites
	s = "Action Match\nUser *\nDesc desc\nSNI *\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	// Add another desc
	s = "Action Match\nDesc desc3\nURI example8.com\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nUser *\nDesc desc4*\nHost example9.com\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = "Action Match\nUser admin*\nDesc desc5*\nHost example10.com*\nDstPort 443*\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = filter_rule_str(opts->filter_rules);

	fail_unless(!strcmp(strstr(s, "filter rule 9: "),
		"filter rule 9: site=example4.com, port=, ip=, user=admin1, desc=desc1, exact=site||||, all=|||, action=||||match, log=|||||, apply to=|||host|, precedence=4\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 10: site=example5.com, port=, ip=, user=admin2, desc=desc2, exact=site||||, all=|||, action=||||match, log=|||||, apply to=|||host|, precedence=4\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 11: site=example6.com, port=, ip=, user=daemon, desc=desc2, exact=site|||user|desc, all=|||, action=||||match, log=|||||, apply to=|||host|, precedence=4\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 12: site=example7.com, port=, ip=, user=, desc=desc, exact=site||||desc, all=|users||, action=||||match, log=|||||, apply to=|||host|, precedence=3\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 13: site=, port=, ip=, user=, desc=desc, exact=||||desc, all=|users|sites|, action=||||match, log=|||||, apply to=|sni|||, precedence=3\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 14: site=example8.com, port=, ip=, user=, desc=desc3, exact=site||||desc, all=|||, action=||||match, log=|||||, apply to=||||uri, precedence=3\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 15: site=example9.com, port=, ip=, user=, desc=desc4, exact=site||||, all=|users||, action=||||match, log=|||||, apply to=|||host|, precedence=3\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 16: site=example10.com, port=443, ip=, user=admin, desc=desc5, exact=||||, all=|||, action=||||match, log=|||||, apply to=|||host|, precedence=5\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192"),
		"failed to parse rule tail: %s", strstr(s, "filter rule 9: "));

	// Trim the tail
	char *p = strstr(s, "filter rule 9: ");
	*p = '\0';

	fail_unless(!strcmp(s,
		"filter rule 0: site=example.com, port=, ip=, user=root, desc=desc, exact=site|||user|desc, all=|||, action=divert||||, log=|||||, apply to=|||host|, precedence=4\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 1: site=example.com, port=443, ip=, user=root, desc=desc, exact=site|port||user|desc, all=|||, action=|split|||, log=connect|master|cert|content|pcap|mirror, apply to=|||host|, precedence=6\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 2: site=example.com, port=, ip=, user=root, desc=desc, exact=site|||user|desc, all=|||, action=||pass||, log=!connect||!cert||!pcap|, apply to=|||host|, precedence=5\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 3: site=example.com, port=, ip=, user=root, desc=desc, exact=site|||user|desc, all=|||, action=|||block|, log=|||||, apply to=|||host|, precedence=4\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 4: site=example2.com, port=443, ip=, user=root, desc=desc, exact=site|port||user|desc, all=|||, action=||||match, log=|||||, apply to=|||host|, precedence=5\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 5: site=example.com, port=, ip=, user=daemon, desc=desc, exact=site|||user|desc, all=|||, action=||||match, log=|||||, apply to=|||host|, precedence=4\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 6: site=, port=443, ip=, user=daemon, desc=desc, exact=|port||user|desc, all=||sites|, action=||||match, log=|||||, apply to=|||host|, precedence=5\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 7: site=.example.com, port=, ip=, user=daemon, desc=desc, exact=|||user|desc, all=|||, action=||||match, log=|||||, apply to=|||host|, precedence=4\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 8: site=example3.com, port=, ip=, user=daemon, desc=desc, exact=site|||user|desc, all=|||, action=||||match, log=|||||, apply to=|||host|, precedence=4\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"),
		"failed to parse rule head: %s", s);

	free(s);

	opts->filter = filter_set(opts->filter_rules, "sslproxy", tmp_opts);

	s = filter_str(opts->filter);

	fail_unless(!strcmp(strstr(s, "userdesc_filter_substring->\n"),
"userdesc_filter_substring->\n"
" user 0 admin (substring)=\n"
"  desc substring:\n"
"   desc 0 desc5 (substring)=\n"
"    host substring:\n"
"      0: example10.com (substring, action=||||, log=|||||, precedence=0)\n"
"        port substring:\n"
"          0: 443 (substring, action=||||match, log=|||||, precedence=5\n"
"            conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
" user 1 admin1 (substring)=\n"
"  desc substring:\n"
"   desc 0 desc1 (substring)=\n"
"    host exact:\n"
"      0: example4.com (exact, action=||||match, log=|||||, precedence=4\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
" user 2 admin2 (substring)=\n"
"  desc substring:\n"
"   desc 0 desc2 (substring)=\n"
"    host exact:\n"
"      0: example5.com (exact, action=||||match, log=|||||, precedence=4\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"user_filter_exact->\n"
"user_filter_substring->\n"
"desc_filter_exact->\n"
"   desc 0 desc (exact)=\n"
"    sni all:\n"
"      0:  (all_sites, substring, action=||||match, log=|||||, precedence=3\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"    host exact:\n"
"      0: example7.com (exact, action=||||match, log=|||||, precedence=3\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"   desc 1 desc3 (exact)=\n"
"    uri exact:\n"
"      0: example8.com (exact, action=||||match, log=|||||, precedence=3\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"desc_filter_substring->\n"
"   desc 0 desc4 (substring)=\n"
"    host exact:\n"
"      0: example9.com (exact, action=||||match, log=|||||, precedence=3\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"user_filter_all->\n"
"ip_filter_exact->\n"
"ip_filter_substring->\n"
"filter_all->\n"), "failed to translate rule tail: %s", strstr(s, "userdesc_filter_substring->\n"));

	// Trim the tail
	p = strstr(s, "userdesc_filter_substring->\n");
	*p = '\0';

	fail_unless(!strcmp(s, "filter=>\n"
"userdesc_filter_exact->\n"
" user 0 daemon (exact)=\n"
"  desc exact:\n"
"   desc 0 desc (exact)=\n"
"    host exact:\n"
"      0: example.com (exact, action=||||match, log=|||||, precedence=4\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"      1: example3.com (exact, action=||||match, log=|||||, precedence=4\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"    host substring:\n"
"      0: .example.com (substring, action=||||match, log=|||||, precedence=4\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"    host all:\n"
"      0:  (all_sites, substring, action=||||, log=|||||, precedence=0)\n"
"        port exact:\n"
"          0: 443 (exact, action=||||match, log=|||||, precedence=5\n"
"            conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"   desc 1 desc2 (exact)=\n"
"    host exact:\n"
"      0: example6.com (exact, action=||||match, log=|||||, precedence=4\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
" user 1 root (exact)=\n"
"  desc exact:\n"
"   desc 0 desc (exact)=\n"
"    host exact:\n"
"      0: example.com (exact, action=divert||pass||, log=!connect||!cert||!pcap|, precedence=5\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"        port exact:\n"
"          0: 443 (exact, action=|split|||, log=connect|master|cert|content|pcap|mirror, precedence=6\n"
"            conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"      1: example2.com (exact, action=||||, log=|||||, precedence=0)\n"
"        port exact:\n"
"          0: 443 (exact, action=||||match, log=|||||, precedence=5\n"
"            conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
			), "failed to translate rule head: %s", s);

	free(s);

	opts_free(opts);
	conn_opts_free(conn_opts);
	tmp_opts_free(tmp_opts);
}
END_TEST
#endif /* !WITHOUT_USERAUTH */

START_TEST(set_filter_struct_13)
{
	char *s;
	int rv;
	opts_t *opts = opts_new();
	conn_opts_t *conn_opts = conn_opts_new();

	tmp_opts_t *tmp_opts = malloc(sizeof (tmp_opts_t));
	memset(tmp_opts, 0, sizeof (tmp_opts_t));

	FILE *f;
	unsigned int line_num = 0;

	s = strdup("$ips 192.168.0.1 192.168.0.2*");
	rv = filter_macro_set(opts, s, 0);
	fail_unless(rv == 0, "failed to set macro");
	free(s);

	s = strdup("$dstips 192.168.0.3 192.168.0.4*");
	rv = filter_macro_set(opts, s, 0);
	fail_unless(rv == 0, "failed to set macro");
	free(s);

	s = strdup("$ports 80* 443");
	rv = filter_macro_set(opts, s, 0);
	fail_unless(rv == 0, "failed to set macro");
	free(s);

	s = strdup("$logs !master !pcap");
	rv = filter_macro_set(opts, s, 0);
	fail_unless(rv == 0, "failed to set macro");
	free(s);

	s = "Action Match\nSrcIp $ips\nDstIp $dstips\nDstPort $ports\nLog $logs\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = filter_rule_str(opts->filter_rules);
#ifndef WITHOUT_USERAUTH
	fail_unless(!strcmp(s,
		"filter rule 0: site=192.168.0.3, port=80, ip=192.168.0.1, user=, desc=, exact=site||ip||, all=|||, action=||||match, log=|!master||||, apply to=dstip||||, precedence=4\n"
		"filter rule 1: site=192.168.0.3, port=80, ip=192.168.0.1, user=, desc=, exact=site||ip||, all=|||, action=||||match, log=||||!pcap|, apply to=dstip||||, precedence=4\n"
		"filter rule 2: site=192.168.0.3, port=443, ip=192.168.0.1, user=, desc=, exact=site|port|ip||, all=|||, action=||||match, log=|!master||||, apply to=dstip||||, precedence=4\n"
		"filter rule 3: site=192.168.0.3, port=443, ip=192.168.0.1, user=, desc=, exact=site|port|ip||, all=|||, action=||||match, log=||||!pcap|, apply to=dstip||||, precedence=4\n"
		"filter rule 4: site=192.168.0.4, port=80, ip=192.168.0.1, user=, desc=, exact=||ip||, all=|||, action=||||match, log=|!master||||, apply to=dstip||||, precedence=4\n"
		"filter rule 5: site=192.168.0.4, port=80, ip=192.168.0.1, user=, desc=, exact=||ip||, all=|||, action=||||match, log=||||!pcap|, apply to=dstip||||, precedence=4\n"
		"filter rule 6: site=192.168.0.4, port=443, ip=192.168.0.1, user=, desc=, exact=|port|ip||, all=|||, action=||||match, log=|!master||||, apply to=dstip||||, precedence=4\n"
		"filter rule 7: site=192.168.0.4, port=443, ip=192.168.0.1, user=, desc=, exact=|port|ip||, all=|||, action=||||match, log=||||!pcap|, apply to=dstip||||, precedence=4\n"
		"filter rule 8: site=192.168.0.3, port=80, ip=192.168.0.2, user=, desc=, exact=site||||, all=|||, action=||||match, log=|!master||||, apply to=dstip||||, precedence=4\n"
		"filter rule 9: site=192.168.0.3, port=80, ip=192.168.0.2, user=, desc=, exact=site||||, all=|||, action=||||match, log=||||!pcap|, apply to=dstip||||, precedence=4\n"
		"filter rule 10: site=192.168.0.3, port=443, ip=192.168.0.2, user=, desc=, exact=site|port|||, all=|||, action=||||match, log=|!master||||, apply to=dstip||||, precedence=4\n"
		"filter rule 11: site=192.168.0.3, port=443, ip=192.168.0.2, user=, desc=, exact=site|port|||, all=|||, action=||||match, log=||||!pcap|, apply to=dstip||||, precedence=4\n"
		"filter rule 12: site=192.168.0.4, port=80, ip=192.168.0.2, user=, desc=, exact=||||, all=|||, action=||||match, log=|!master||||, apply to=dstip||||, precedence=4\n"
		"filter rule 13: site=192.168.0.4, port=80, ip=192.168.0.2, user=, desc=, exact=||||, all=|||, action=||||match, log=||||!pcap|, apply to=dstip||||, precedence=4\n"
		"filter rule 14: site=192.168.0.4, port=443, ip=192.168.0.2, user=, desc=, exact=|port|||, all=|||, action=||||match, log=|!master||||, apply to=dstip||||, precedence=4\n"
		"filter rule 15: site=192.168.0.4, port=443, ip=192.168.0.2, user=, desc=, exact=|port|||, all=|||, action=||||match, log=||||!pcap|, apply to=dstip||||, precedence=4"),
		"failed to parse rule: %s", s);
#else /* WITHOUT_USERAUTH */
	fail_unless(!strcmp(s,
		"filter rule 0: site=192.168.0.3, port=80, ip=192.168.0.1, exact=site||ip, all=||, action=||||match, log=|!master||||, apply to=dstip||||, precedence=4\n"
		"filter rule 1: site=192.168.0.3, port=80, ip=192.168.0.1, exact=site||ip, all=||, action=||||match, log=||||!pcap|, apply to=dstip||||, precedence=4\n"
		"filter rule 2: site=192.168.0.3, port=443, ip=192.168.0.1, exact=site|port|ip, all=||, action=||||match, log=|!master||||, apply to=dstip||||, precedence=4\n"
		"filter rule 3: site=192.168.0.3, port=443, ip=192.168.0.1, exact=site|port|ip, all=||, action=||||match, log=||||!pcap|, apply to=dstip||||, precedence=4\n"
		"filter rule 4: site=192.168.0.4, port=80, ip=192.168.0.1, exact=||ip, all=||, action=||||match, log=|!master||||, apply to=dstip||||, precedence=4\n"
		"filter rule 5: site=192.168.0.4, port=80, ip=192.168.0.1, exact=||ip, all=||, action=||||match, log=||||!pcap|, apply to=dstip||||, precedence=4\n"
		"filter rule 6: site=192.168.0.4, port=443, ip=192.168.0.1, exact=|port|ip, all=||, action=||||match, log=|!master||||, apply to=dstip||||, precedence=4\n"
		"filter rule 7: site=192.168.0.4, port=443, ip=192.168.0.1, exact=|port|ip, all=||, action=||||match, log=||||!pcap|, apply to=dstip||||, precedence=4\n"
		"filter rule 8: site=192.168.0.3, port=80, ip=192.168.0.2, exact=site||, all=||, action=||||match, log=|!master||||, apply to=dstip||||, precedence=4\n"
		"filter rule 9: site=192.168.0.3, port=80, ip=192.168.0.2, exact=site||, all=||, action=||||match, log=||||!pcap|, apply to=dstip||||, precedence=4\n"
		"filter rule 10: site=192.168.0.3, port=443, ip=192.168.0.2, exact=site|port|, all=||, action=||||match, log=|!master||||, apply to=dstip||||, precedence=4\n"
		"filter rule 11: site=192.168.0.3, port=443, ip=192.168.0.2, exact=site|port|, all=||, action=||||match, log=||||!pcap|, apply to=dstip||||, precedence=4\n"
		"filter rule 12: site=192.168.0.4, port=80, ip=192.168.0.2, exact=||, all=||, action=||||match, log=|!master||||, apply to=dstip||||, precedence=4\n"
		"filter rule 13: site=192.168.0.4, port=80, ip=192.168.0.2, exact=||, all=||, action=||||match, log=||||!pcap|, apply to=dstip||||, precedence=4\n"
		"filter rule 14: site=192.168.0.4, port=443, ip=192.168.0.2, exact=|port|, all=||, action=||||match, log=|!master||||, apply to=dstip||||, precedence=4\n"
		"filter rule 15: site=192.168.0.4, port=443, ip=192.168.0.2, exact=|port|, all=||, action=||||match, log=||||!pcap|, apply to=dstip||||, precedence=4"),
		"failed to parse rule: %s", s);
#endif /* WITHOUT_USERAUTH */
	free(s);

	opts->filter = filter_set(opts->filter_rules, "sslproxy", tmp_opts);

	s = filter_str(opts->filter);
#ifndef WITHOUT_USERAUTH
	fail_unless(!strcmp(s, "filter=>\n"
"userdesc_filter_exact->\n"
"userdesc_filter_substring->\n"
"user_filter_exact->\n"
"user_filter_substring->\n"
"desc_filter_exact->\n"
"desc_filter_substring->\n"
"user_filter_all->\n"
"ip_filter_exact->\n"
"  ip 0 192.168.0.1 (exact)=\n"
"    ip exact:\n"
"      0: 192.168.0.3 (exact, action=||||, log=|||||, precedence=0)\n"
"        port exact:\n"
"          0: 443 (exact, action=||||match, log=|!master|||!pcap|, precedence=4)\n"
"        port substring:\n"
"          0: 80 (substring, action=||||match, log=|!master|||!pcap|, precedence=4)\n"
"    ip substring:\n"
"      0: 192.168.0.4 (substring, action=||||, log=|||||, precedence=0)\n"
"        port exact:\n"
"          0: 443 (exact, action=||||match, log=|!master|||!pcap|, precedence=4)\n"
"        port substring:\n"
"          0: 80 (substring, action=||||match, log=|!master|||!pcap|, precedence=4)\n"
"ip_filter_substring->\n"
"  ip 0 192.168.0.2 (substring)=\n"
"    ip exact:\n"
"      0: 192.168.0.3 (exact, action=||||, log=|||||, precedence=0)\n"
"        port exact:\n"
"          0: 443 (exact, action=||||match, log=|!master|||!pcap|, precedence=4)\n"
"        port substring:\n"
"          0: 80 (substring, action=||||match, log=|!master|||!pcap|, precedence=4)\n"
"    ip substring:\n"
"      0: 192.168.0.4 (substring, action=||||, log=|||||, precedence=0)\n"
"        port exact:\n"
"          0: 443 (exact, action=||||match, log=|!master|||!pcap|, precedence=4)\n"
"        port substring:\n"
"          0: 80 (substring, action=||||match, log=|!master|||!pcap|, precedence=4)\n"
"filter_all->\n"), "failed to translate rule: %s", s);
#else /* WITHOUT_USERAUTH */
	fail_unless(!strcmp(s, "filter=>\n"
"ip_filter_exact->\n"
"  ip 0 192.168.0.1 (exact)=\n"
"    ip exact:\n"
"      0: 192.168.0.3 (exact, action=||||, log=|||||, precedence=0)\n"
"        port exact:\n"
"          0: 443 (exact, action=||||match, log=|!master|||!pcap|, precedence=4)\n"
"        port substring:\n"
"          0: 80 (substring, action=||||match, log=|!master|||!pcap|, precedence=4)\n"
"    ip substring:\n"
"      0: 192.168.0.4 (substring, action=||||, log=|||||, precedence=0)\n"
"        port exact:\n"
"          0: 443 (exact, action=||||match, log=|!master|||!pcap|, precedence=4)\n"
"        port substring:\n"
"          0: 80 (substring, action=||||match, log=|!master|||!pcap|, precedence=4)\n"
"ip_filter_substring->\n"
"  ip 0 192.168.0.2 (substring)=\n"
"    ip exact:\n"
"      0: 192.168.0.3 (exact, action=||||, log=|||||, precedence=0)\n"
"        port exact:\n"
"          0: 443 (exact, action=||||match, log=|!master|||!pcap|, precedence=4)\n"
"        port substring:\n"
"          0: 80 (substring, action=||||match, log=|!master|||!pcap|, precedence=4)\n"
"    ip substring:\n"
"      0: 192.168.0.4 (substring, action=||||, log=|||||, precedence=0)\n"
"        port exact:\n"
"          0: 443 (exact, action=||||match, log=|!master|||!pcap|, precedence=4)\n"
"        port substring:\n"
"          0: 80 (substring, action=||||match, log=|!master|||!pcap|, precedence=4)\n"
"filter_all->\n"), "failed to translate rule: %s", s);
#endif /* WITHOUT_USERAUTH */
	free(s);

	opts_free(opts);
	conn_opts_free(conn_opts);
	tmp_opts_free(tmp_opts);
}
END_TEST

#ifndef WITHOUT_USERAUTH
START_TEST(set_filter_struct_14)
{
	char *s;
	int rv;
	opts_t *opts = opts_new();
	conn_opts_t *conn_opts = conn_opts_new();

	tmp_opts_t *tmp_opts = malloc(sizeof (tmp_opts_t));
	memset(tmp_opts, 0, sizeof (tmp_opts_t));

	FILE *f;
	unsigned int line_num = 0;

	s = strdup("$users root admin*");
	rv = filter_macro_set(opts, s, 0);
	fail_unless(rv == 0, "failed to set macro");
	free(s);

	s = strdup("$descs desc1 desc2*");
	rv = filter_macro_set(opts, s, 0);
	fail_unless(rv == 0, "failed to set macro");
	free(s);

	s = strdup("$sites site1 site2*");
	rv = filter_macro_set(opts, s, 0);
	fail_unless(rv == 0, "failed to set macro");
	free(s);

	// check errors out if we add all log actions to the macro:
	// "../../src/check_pack.c:306: Message string too long"
	// Also, the compiler gives:
	// warning: string length ‘4186’ is greater than the length ‘4095’ ISO C99 compilers are required to support [-Woverlength-strings]
	// so use 2 log actions only
	s = strdup("$logs connect content");
	rv = filter_macro_set(opts, s, 0);
	fail_unless(rv == 0, "failed to set macro");
	free(s);

	s = "Action Match\nUser $users\nDesc $descs\nSNI $sites\nLog $logs\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = filter_rule_str(opts->filter_rules);

	fail_unless(!strcmp(strstr(s, "filter rule 8: "),
		"filter rule 8: site=site1, port=, ip=, user=admin, desc=desc1, exact=site||||desc, all=|||, action=||||match, log=connect|||||, apply to=|sni|||, precedence=5\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 9: site=site1, port=, ip=, user=admin, desc=desc1, exact=site||||desc, all=|||, action=||||match, log=|||content||, apply to=|sni|||, precedence=5\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 10: site=site2, port=, ip=, user=admin, desc=desc1, exact=||||desc, all=|||, action=||||match, log=connect|||||, apply to=|sni|||, precedence=5\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 11: site=site2, port=, ip=, user=admin, desc=desc1, exact=||||desc, all=|||, action=||||match, log=|||content||, apply to=|sni|||, precedence=5\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 12: site=site1, port=, ip=, user=admin, desc=desc2, exact=site||||, all=|||, action=||||match, log=connect|||||, apply to=|sni|||, precedence=5\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 13: site=site1, port=, ip=, user=admin, desc=desc2, exact=site||||, all=|||, action=||||match, log=|||content||, apply to=|sni|||, precedence=5\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 14: site=site2, port=, ip=, user=admin, desc=desc2, exact=||||, all=|||, action=||||match, log=connect|||||, apply to=|sni|||, precedence=5\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 15: site=site2, port=, ip=, user=admin, desc=desc2, exact=||||, all=|||, action=||||match, log=|||content||, apply to=|sni|||, precedence=5\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192"),
		"failed to parse rule tail: %s", strstr(s, "filter rule 8: "));

	// Trim the tail
	char *p = strstr(s, "filter rule 8: ");
	*p = '\0';

	fail_unless(!strcmp(s,
		"filter rule 0: site=site1, port=, ip=, user=root, desc=desc1, exact=site|||user|desc, all=|||, action=||||match, log=connect|||||, apply to=|sni|||, precedence=5\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 1: site=site1, port=, ip=, user=root, desc=desc1, exact=site|||user|desc, all=|||, action=||||match, log=|||content||, apply to=|sni|||, precedence=5\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 2: site=site2, port=, ip=, user=root, desc=desc1, exact=|||user|desc, all=|||, action=||||match, log=connect|||||, apply to=|sni|||, precedence=5\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 3: site=site2, port=, ip=, user=root, desc=desc1, exact=|||user|desc, all=|||, action=||||match, log=|||content||, apply to=|sni|||, precedence=5\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 4: site=site1, port=, ip=, user=root, desc=desc2, exact=site|||user|, all=|||, action=||||match, log=connect|||||, apply to=|sni|||, precedence=5\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 5: site=site1, port=, ip=, user=root, desc=desc2, exact=site|||user|, all=|||, action=||||match, log=|||content||, apply to=|sni|||, precedence=5\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 6: site=site2, port=, ip=, user=root, desc=desc2, exact=|||user|, all=|||, action=||||match, log=connect|||||, apply to=|sni|||, precedence=5\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 7: site=site2, port=, ip=, user=root, desc=desc2, exact=|||user|, all=|||, action=||||match, log=|||content||, apply to=|sni|||, precedence=5\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"),
		"failed to parse rule head: %s", s);

	free(s);

	opts->filter = filter_set(opts->filter_rules, "sslproxy", tmp_opts);

	s = filter_str(opts->filter);
	fail_unless(!strcmp(s, "filter=>\n"
"userdesc_filter_exact->\n"
" user 0 root (exact)=\n"
"  desc exact:\n"
"   desc 0 desc1 (exact)=\n"
"    sni exact:\n"
"      0: site1 (exact, action=||||match, log=connect|||content||, precedence=5\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"    sni substring:\n"
"      0: site2 (substring, action=||||match, log=connect|||content||, precedence=5\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"  desc substring:\n"
"   desc 0 desc2 (substring)=\n"
"    sni exact:\n"
"      0: site1 (exact, action=||||match, log=connect|||content||, precedence=5\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"    sni substring:\n"
"      0: site2 (substring, action=||||match, log=connect|||content||, precedence=5\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"userdesc_filter_substring->\n"
" user 0 admin (substring)=\n"
"  desc exact:\n"
"   desc 0 desc1 (exact)=\n"
"    sni exact:\n"
"      0: site1 (exact, action=||||match, log=connect|||content||, precedence=5\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"    sni substring:\n"
"      0: site2 (substring, action=||||match, log=connect|||content||, precedence=5\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"  desc substring:\n"
"   desc 0 desc2 (substring)=\n"
"    sni exact:\n"
"      0: site1 (exact, action=||||match, log=connect|||content||, precedence=5\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"    sni substring:\n"
"      0: site2 (substring, action=||||match, log=connect|||content||, precedence=5\n"
"        conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"user_filter_exact->\n"
"user_filter_substring->\n"
"desc_filter_exact->\n"
"desc_filter_substring->\n"
"user_filter_all->\n"
"ip_filter_exact->\n"
"ip_filter_substring->\n"
"filter_all->\n"), "failed to translate rule: %s", s);
	free(s);

	opts_free(opts);
	conn_opts_free(conn_opts);
	tmp_opts_free(tmp_opts);
}
END_TEST

START_TEST(set_filter_struct_15)
{
	char *s;
	int rv;
	opts_t *opts = opts_new();
	conn_opts_t *conn_opts = conn_opts_new();

	tmp_opts_t *tmp_opts = malloc(sizeof (tmp_opts_t));
	memset(tmp_opts, 0, sizeof (tmp_opts_t));

	FILE *f;
	unsigned int line_num = 0;

	s = strdup("$users root admin*");
	rv = filter_macro_set(opts, s, 0);
	fail_unless(rv == 0, "failed to set macro");
	free(s);

	s = strdup("$descs desc1 desc2*");
	rv = filter_macro_set(opts, s, 0);
	fail_unless(rv == 0, "failed to set macro");
	free(s);

	s = strdup("$sites site1* site2");
	rv = filter_macro_set(opts, s, 0);
	fail_unless(rv == 0, "failed to set macro");
	free(s);

	// Syntactically right, but semantically redundant/useless
	s = strdup("$ports 80* *");
	rv = filter_macro_set(opts, s, 0);
	fail_unless(rv == 0, "failed to set macro");
	free(s);

	// check errors out if we add all log actions to the macro:
	// "../../src/check_pack.c:306: Message string too long"
	// Also, the compiler gives:
	// warning: string length ‘4186’ is greater than the length ‘4095’ ISO C99 compilers are required to support [-Woverlength-strings]
	// so use 1 log action only
	s = strdup("$logs pcap");
	rv = filter_macro_set(opts, s, 0);
	fail_unless(rv == 0, "failed to set macro");
	free(s);

	s = "Action Match\nUser $users\nDesc $descs\nCN $sites\nDstPort $ports\nLog $logs\nUserAuth yes\n}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = filter_rule_str(opts->filter_rules);

	fail_unless(!strcmp(strstr(s, "filter rule 8: "),
		"filter rule 8: site=site1, port=80, ip=, user=admin, desc=desc1, exact=||||desc, all=|||, action=||||match, log=||||pcap|, apply to=||cn||, precedence=6\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 9: site=site1, port=, ip=, user=admin, desc=desc1, exact=||||desc, all=|||ports, action=||||match, log=||||pcap|, apply to=||cn||, precedence=6\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 10: site=site2, port=80, ip=, user=admin, desc=desc1, exact=site||||desc, all=|||, action=||||match, log=||||pcap|, apply to=||cn||, precedence=6\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 11: site=site2, port=, ip=, user=admin, desc=desc1, exact=site||||desc, all=|||ports, action=||||match, log=||||pcap|, apply to=||cn||, precedence=6\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 12: site=site1, port=80, ip=, user=admin, desc=desc2, exact=||||, all=|||, action=||||match, log=||||pcap|, apply to=||cn||, precedence=6\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 13: site=site1, port=, ip=, user=admin, desc=desc2, exact=||||, all=|||ports, action=||||match, log=||||pcap|, apply to=||cn||, precedence=6\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 14: site=site2, port=80, ip=, user=admin, desc=desc2, exact=site||||, all=|||, action=||||match, log=||||pcap|, apply to=||cn||, precedence=6\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 15: site=site2, port=, ip=, user=admin, desc=desc2, exact=site||||, all=|||ports, action=||||match, log=||||pcap|, apply to=||cn||, precedence=6\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192"),
		"failed to parse rule tail: %s", strstr(s, "filter rule 8: "));

	// Trim the tail
	char *p = strstr(s, "filter rule 8: ");
	*p = '\0';

	fail_unless(!strcmp(s,
		"filter rule 0: site=site1, port=80, ip=, user=root, desc=desc1, exact=|||user|desc, all=|||, action=||||match, log=||||pcap|, apply to=||cn||, precedence=6\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 1: site=site1, port=, ip=, user=root, desc=desc1, exact=|||user|desc, all=|||ports, action=||||match, log=||||pcap|, apply to=||cn||, precedence=6\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 2: site=site2, port=80, ip=, user=root, desc=desc1, exact=site|||user|desc, all=|||, action=||||match, log=||||pcap|, apply to=||cn||, precedence=6\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 3: site=site2, port=, ip=, user=root, desc=desc1, exact=site|||user|desc, all=|||ports, action=||||match, log=||||pcap|, apply to=||cn||, precedence=6\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 4: site=site1, port=80, ip=, user=root, desc=desc2, exact=|||user|, all=|||, action=||||match, log=||||pcap|, apply to=||cn||, precedence=6\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 5: site=site1, port=, ip=, user=root, desc=desc2, exact=|||user|, all=|||ports, action=||||match, log=||||pcap|, apply to=||cn||, precedence=6\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 6: site=site2, port=80, ip=, user=root, desc=desc2, exact=site|||user|, all=|||, action=||||match, log=||||pcap|, apply to=||cn||, precedence=6\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"
		"filter rule 7: site=site2, port=, ip=, user=root, desc=desc2, exact=site|||user|, all=|||ports, action=||||match, log=||||pcap|, apply to=||cn||, precedence=6\n"
		"  conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192\n"),
		"failed to parse rule head: %s", s);

	free(s);

	opts->filter = filter_set(opts->filter_rules, "sslproxy", tmp_opts);

	s = filter_str(opts->filter);

	fail_unless(!strcmp(strstr(s, "userdesc_filter_substring->\n"),
"userdesc_filter_substring->\n"
" user 0 admin (substring)=\n"
"  desc exact:\n"
"   desc 0 desc1 (exact)=\n"
"    cn exact:\n"
"      0: site2 (exact, action=||||, log=|||||, precedence=0)\n"
"        port substring:\n"
"          0: 80 (substring, action=||||match, log=||||pcap|, precedence=6\n"
"            conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"        port all:\n"
"          0:  (all_ports, substring, action=||||match, log=||||pcap|, precedence=6\n"
"            conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"    cn substring:\n"
"      0: site1 (substring, action=||||, log=|||||, precedence=0)\n"
"        port substring:\n"
"          0: 80 (substring, action=||||match, log=||||pcap|, precedence=6\n"
"            conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"        port all:\n"
"          0:  (all_ports, substring, action=||||match, log=||||pcap|, precedence=6\n"
"            conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"  desc substring:\n"
"   desc 0 desc2 (substring)=\n"
"    cn exact:\n"
"      0: site2 (exact, action=||||, log=|||||, precedence=0)\n"
"        port substring:\n"
"          0: 80 (substring, action=||||match, log=||||pcap|, precedence=6\n"
"            conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"        port all:\n"
"          0:  (all_ports, substring, action=||||match, log=||||pcap|, precedence=6\n"
"            conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"    cn substring:\n"
"      0: site1 (substring, action=||||, log=|||||, precedence=0)\n"
"        port substring:\n"
"          0: 80 (substring, action=||||match, log=||||pcap|, precedence=6\n"
"            conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"        port all:\n"
"          0:  (all_ports, substring, action=||||match, log=||||pcap|, precedence=6\n"
"            conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"user_filter_exact->\n"
"user_filter_substring->\n"
"desc_filter_exact->\n"
"desc_filter_substring->\n"
"user_filter_all->\n"
"ip_filter_exact->\n"
"ip_filter_substring->\n"
"filter_all->\n"), "failed to translate rule tail: %s", strstr(s, "userdesc_filter_substring->\n"));

	// Trim the tail
	p = strstr(s, "userdesc_filter_substring->\n");
	*p = '\0';

	fail_unless(!strcmp(s, "filter=>\n"
"userdesc_filter_exact->\n"
" user 0 root (exact)=\n"
"  desc exact:\n"
"   desc 0 desc1 (exact)=\n"
"    cn exact:\n"
"      0: site2 (exact, action=||||, log=|||||, precedence=0)\n"
"        port substring:\n"
"          0: 80 (substring, action=||||match, log=||||pcap|, precedence=6\n"
"            conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"        port all:\n"
"          0:  (all_ports, substring, action=||||match, log=||||pcap|, precedence=6\n"
"            conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"    cn substring:\n"
"      0: site1 (substring, action=||||, log=|||||, precedence=0)\n"
"        port substring:\n"
"          0: 80 (substring, action=||||match, log=||||pcap|, precedence=6\n"
"            conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"        port all:\n"
"          0:  (all_ports, substring, action=||||match, log=||||pcap|, precedence=6\n"
"            conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"  desc substring:\n"
"   desc 0 desc2 (substring)=\n"
"    cn exact:\n"
"      0: site2 (exact, action=||||, log=|||||, precedence=0)\n"
"        port substring:\n"
"          0: 80 (substring, action=||||match, log=||||pcap|, precedence=6\n"
"            conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"        port all:\n"
"          0:  (all_ports, substring, action=||||match, log=||||pcap|, precedence=6\n"
"            conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"    cn substring:\n"
"      0: site1 (substring, action=||||, log=|||||, precedence=0)\n"
"        port substring:\n"
"          0: 80 (substring, action=||||match, log=||||pcap|, precedence=6\n"
"            conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
"        port all:\n"
"          0:  (all_ports, substring, action=||||match, log=||||pcap|, precedence=6\n"
"            conn opts: negotiate>=tls10<=tls13|no ciphers|no ciphersuites|no ecdhcurve|no leafcrlurl|remove_http_referer|verify_peer|user_auth|no user_auth_url|300|8192)\n"
			), "failed to translate rule head: %s", s);

	free(s);

	opts_free(opts);
	conn_opts_free(conn_opts);
	tmp_opts_free(tmp_opts);
}
END_TEST
#endif /* !WITHOUT_USERAUTH */

START_TEST(set_filter_struct_16)
{
	char *s;
	int rv;
	opts_t *opts = opts_new();
	conn_opts_t *conn_opts = conn_opts_new();

	tmp_opts_t *tmp_opts = malloc(sizeof (tmp_opts_t));
	memset(tmp_opts, 0, sizeof (tmp_opts_t));

	FILE *f;
	unsigned int line_num = 0;

	s = "Action Match\n"
		"SrcIp 192.168.0.1\n"
		"DstIp 192.168.0.2\n"
		"Log connect\n"
		"ReconnectSSL yes\n"
		"DenyOCSP no\n"
		"Passthrough yes\n"
		"CACert ../testproxy/ca.crt\n"
		"CAKey ../testproxy/ca.key\n"
		"ClientCert ../testproxy/ca2.crt\n"
		"ClientKey ../testproxy/ca2.key\n"
		"CAChain ../testproxy/server.crt\n"
		"LeafCRLURL http://example1.com/example1.crl\n"
		//"DHGroupParams /etc/sslproxy/dh.pem\n"
		"ECDHCurve prime192v1\n"
		"SSLCompression yes\n"
		"ForceSSLProto tls11\n"
		"DisableSSLProto tls13\n"
		"EnableSSLProto tls1\n"
		"MinSSLProto tls10\n"
		"MaxSSLProto tls11\n"
		"Ciphers LOW\n"
		"CipherSuites TLS_AES_128_CCM_SHA256\n"
		"RemoveHTTPAcceptEncoding no\n"
		"RemoveHTTPReferer no\n"
		"VerifyPeer no\n"
		"AllowWrongHost yes\n"
#ifndef WITHOUT_USERAUTH
		"UserAuth no\n"
		"UserTimeout 1200\n"
		"UserAuthURL https://192.168.0.12/userdblogin1.php\n"
#endif /* !WITHOUT_USERAUTH */
		"ValidateProto no\n"
		"MaxHTTPHeaderSize 2048\n"
		"}";
	f = fmemopen(s, strlen(s), "r");
	rv = load_filterrule_struct(opts, conn_opts, "sslproxy", &line_num, f, tmp_opts);
	fclose(f);
	fail_unless(rv == 0, "failed to parse rule");

	s = filter_rule_str(opts->filter_rules);
#ifndef WITHOUT_USERAUTH
	fail_unless(!strcmp(s,
		"filter rule 0: site=192.168.0.2, port=, ip=192.168.0.1, user=, desc=, exact=site||ip||, all=|||, action=||||match, log=connect|||||, apply to=dstip||||, precedence=3\n"
		"  conn opts: tls11 -tls13>=tls10<=tls11|no_tls13|passthrough|LOW|TLS_AES_128_CCM_SHA256|prime192v1|http://example1.com/example1.crl|allow_wrong_host|https://192.168.0.12/userdblogin1.php|1200|reconnect_ssl|2048"),
		"failed to parse rule: %s", s);
#else /* WITHOUT_USERAUTH */
	fail_unless(!strcmp(s,
		"filter rule 0: site=192.168.0.2, port=, ip=192.168.0.1, exact=site||ip, all=||, action=||||match, log=connect|||||, apply to=dstip||||, precedence=3\n"
		"  conn opts: tls11 -tls13>=tls10<=tls11|no_tls13|passthrough|LOW|TLS_AES_128_CCM_SHA256|prime192v1|http://example1.com/example1.crl|allow_wrong_host|reconnect_ssl|2048"),
		"failed to parse rule: %s", s);
#endif /* WITHOUT_USERAUTH */
	free(s);

	opts->filter = filter_set(opts->filter_rules, "sslproxy", tmp_opts);

	s = filter_str(opts->filter);
#ifndef WITHOUT_USERAUTH
	fail_unless(!strcmp(s, "filter=>\n"
"userdesc_filter_exact->\n"
"userdesc_filter_substring->\n"
"user_filter_exact->\n"
"user_filter_substring->\n"
"desc_filter_exact->\n"
"desc_filter_substring->\n"
"user_filter_all->\n"
"ip_filter_exact->\n"
"  ip 0 192.168.0.1 (exact)=\n"
"    ip exact:\n"
"      0: 192.168.0.2 (exact, action=||||match, log=connect|||||, precedence=3\n"
"        conn opts: tls11 -tls13>=tls10<=tls11|no_tls13|passthrough|LOW|TLS_AES_128_CCM_SHA256|prime192v1|no leafcrlurl|allow_wrong_host|https://192.168.0.12/userdblogin1.php|1200|reconnect_ssl|2048)\n"
"ip_filter_substring->\n"
"filter_all->\n"), "failed to translate rule: %s", s);
#else /* WITHOUT_USERAUTH */
	fail_unless(!strcmp(s, "filter=>\n"
"ip_filter_exact->\n"
"  ip 0 192.168.0.1 (exact)=\n"
"    ip exact:\n"
"      0: 192.168.0.2 (exact, action=||||match, log=connect|||||, precedence=3\n"
"        conn opts: tls11 -tls13>=tls10<=tls11|no_tls13|passthrough|LOW|TLS_AES_128_CCM_SHA256|prime192v1|no leafcrlurl|allow_wrong_host|reconnect_ssl|2048)\n"
"ip_filter_substring->\n"
"filter_all->\n"), "failed to translate rule: %s", s);
#endif /* WITHOUT_USERAUTH */
	free(s);

	opts_free(opts);
	conn_opts_free(conn_opts);
	tmp_opts_free(tmp_opts);
}
END_TEST

Suite *
filter_struct_suite(void)
{
	Suite *s;
	TCase *tc;
	s = suite_create("filter_struct");

	tc = tcase_create("set_filter_struct");
	tcase_add_test(tc, set_filter_struct_01);
	tcase_add_test(tc, set_filter_struct_02);
#ifndef WITHOUT_USERAUTH
	tcase_add_test(tc, set_filter_struct_03);
#endif /* !WITHOUT_USERAUTH */
	tcase_add_test(tc, set_filter_struct_04);
	tcase_add_test(tc, set_filter_struct_05);
	tcase_add_test(tc, set_filter_struct_06);
#ifndef WITHOUT_USERAUTH
	tcase_add_test(tc, set_filter_struct_07);
#endif /* !WITHOUT_USERAUTH */
	tcase_add_test(tc, set_filter_struct_08);
	tcase_add_test(tc, set_filter_struct_09);
#ifndef WITHOUT_USERAUTH
	tcase_add_test(tc, set_filter_struct_10);
	tcase_add_test(tc, set_filter_struct_11);
	tcase_add_test(tc, set_filter_struct_12);
#endif /* !WITHOUT_USERAUTH */
	tcase_add_test(tc, set_filter_struct_13);
#ifndef WITHOUT_USERAUTH
	tcase_add_test(tc, set_filter_struct_14);
	tcase_add_test(tc, set_filter_struct_15);
#endif /* !WITHOUT_USERAUTH */
	tcase_add_test(tc, set_filter_struct_16);
	suite_add_tcase(s, tc);

	return s;
}

/* vim: set noet ft=c: */