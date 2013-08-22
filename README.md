# gdbus demo

This is not a generic gdbus demo.

It is meant to just show one specific corner case bug.


This shows that method calls being passed to interface NULL are not evaluated when using 
`g_dbus_connection_register_object`, whereas the bare metal C reference implemenatation works as the spec says (it allows omitting the interface (read NULL) when calling a remote function).

### create the binaries

```bash
waf distclean configure build -j
```

### demonstration

Combine one of these

```
build/server-ref.bin
build/client-ref.bin
```

with one of those

```
build/server-gdbus.bin
build/client-gdbus.bin
```

and see what happens.

Also let `gdbus-monitor --session --monitor` run in parallel.

### Notes

The reference demo shown is really crappy as of now.
