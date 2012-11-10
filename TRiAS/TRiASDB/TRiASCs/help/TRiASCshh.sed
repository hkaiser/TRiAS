/helpcontext/ { 
	s/^.*helpcontext(\([^)]*\)).*$/#define \1 /
	p
}
/helpcontext/ !d
