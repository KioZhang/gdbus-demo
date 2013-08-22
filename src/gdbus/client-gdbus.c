#include <glib.h>
#include <glib/gprintf.h>
#include <gio/gio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
#if OLD_GLIB
	g_type_init ();
#endif

	GDBusConnection *con;

	GError *error = NULL;

	con = g_bus_get_sync (G_BUS_TYPE_SESSION, NULL, &error);
	if (error) {
		g_printf ("Failed to get bus access - %i : %s\n", error->code, error->message);
		g_error_free (error); error = NULL;
		return EXIT_FAILURE;
	}

#if 0
	GVariant *result =
	      g_dbus_connection_call_sync (con,
	                               "com.srctwig.bugdemo.server",
	                               "/obj/path",
#if OLD
	                               "com.srctwig.bugdemo.interface",
#else
		                           NULL,
#endif
	                               "doSomething",
	                              g_variant_new ("(s)", "<foo> Hello! </foo>"),
					NULL,/*GVariantType*/
	                              G_DBUS_CALL_FLAGS_NONE,
	                              -1 /* timeout in msec, -1 == default */,
	                              NULL /* cancellable */,
	                              &error);
	if (result)
		g_variant_unref (result);
#else
		GDBusMessage *msg = g_dbus_message_new_method_call ("com.srctwig.bugdemo.server", "/obj/path", NULL/*interfcae*/, "doSomething");
		g_dbus_message_set_body (msg, g_variant_new ("(s)", "<foo> Hello! </foo>"));
		GDBusMessage *resp = g_dbus_connection_send_message_with_reply_sync (con, msg, G_DBUS_SEND_MESSAGE_FLAGS_NONE, -1, NULL, NULL, &error);
		(void)resp; //prevent a warning
#endif
	if (error) {
		g_printf ("Failed to call remote method - %i : %s\n", error->code, error->message);
		g_error_free (error); error = NULL;
		g_object_unref (con);
		return EXIT_FAILURE;
	}


#if 0
	GMainLoop *loop;
	loop = g_main_loop_new (NULL, FALSE);
	g_main_loop_run (loop);
	g_main_loop_unref (loop);
#endif
////////////////////////////////////////////////////////////////////////////////
// cleanup
////////////////////////////////////////////////////////////////////////////////

	g_object_unref (con);
	return EXIT_SUCCESS;
}
