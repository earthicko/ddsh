static int	export_display(void)
{
	// TODO: 구현
	return (0);
}

static int	export_var(char *word)
{
	// TODO: 구현
	(void) word;
	return (0);
}

int	builtin_export(char **argv)
{
	int	stat;

	if (!(argv[0]))
		return (export_display());
	stat = 0;
	while (*argv)
	{
		if (export_var(*argv))
			stat = 1;
		argv++;
	}
	return (stat);
}
