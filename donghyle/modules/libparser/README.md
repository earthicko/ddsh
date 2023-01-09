# 파서 모듈 (libparser)

```c
t_node	*parse_tokens(t_token *tokenarr, int n_tokens);
```

### 의존성 정보

- `libft.a`
- `struct s_token`

# 개요

```c
/*  t_node.h  */
typedef struct s_node
{
	t_list	*childs;
	int		type;
	char	*content;
	int		n_tokens;
}	t_node;

enum e_nodetype
{
	NODETYPE_PIPE_SEQUENCE = 0,
	NODETYPE_SIMPLE_COMMAND,
	NODETYPE_CMD_ELEMENT,
	NODETYPE_IO_REDIRECT,
	NODETYPE_IO_FILE,
	NODETYPE_FILENAME,
	NODETYPE_IO_HERE,
	NODETYPE_HERE_END,
};

/*  parser.h  */
# include "t_node.h"
# include "t_token.h"

typedef struct s_parser
{
	t_token	*tok_start;
	t_token	*tok_curr;
	t_token	*tok_last;
	int		n_tokens;
}	t_parser;

t_node	*parse_tokens(t_token *tokenarr, int n_tokens);
```

이 모듈은 외부에 1개의 인터페이스용 함수와 파싱 결과를 기술하는 자료형을 제공한다.

`parse_tokens()` 함수에 토큰 배열의 첫 원소의 주소와 토큰의 개수를 전달하면 그 파싱 결과가 `t_node *`형 자료로 반환된다. 시스템 오류가 발생하거나 파싱할 수 없는 토큰 배열을 발견할 경우 `NULL`을 반환한다.

## 전용 자료형

`t_node` 자료형은 트리 또는 트리의 한 노드를 상징한다. 노드는 다음과 같은 속성을 가진다.

- `int type`: 이 노드의 타입이다. 타입의 종류는 `enum e_nodetype`이 정의한다.
- `char *content`: 이 노드를 대표하는 토큰의 문자열이다. 어떤 노드는 대표하는 문자열이 없을 수도 있다.
- `t_list *childs`: 이 노드의 자식 노드들을 담은 리스트이다. `libft`를 사용한다.
- `int n_tokens`: 이 노드를 구성하는 데 소모된 토큰의 수이다. 자식의 토큰 수는 포함하지 않는다.

# 동작 원리

## 알고리즘

파서는 토큰의 배열이 다음의 문법과 일치하는지 검사한다.

```BNF
pipe_sequence    :                   simple_command
                 | pipe_sequence '|' simple_command
                 ; N개의 simple_command가 '|'로 이어진 것
                 ; 처음 위치에서 s/c를 만들고, 다음 포인터가 |라면 반복, NULL이라면 종료, 다 아니라면 에러
simple_command   : cmd_element
				 | simple_command cmd_element
				 ;
cmd_element		 : WORD
				 | io_redirect
				 ;
io_redirect      :           io_file
                 |           io_here
                 ; io_file 또는 io_here
io_file          : '<'       filename
                 | '>'       filename
                 | '>>'      filename
                 ; 토큰 2개
filename         : WORD
                 ; 토큰 1개
io_here          : '<<'     here_end
                 ; 토큰 2개
here_end         : WORD                      /* Apply rule 3 */
                 ; 토큰 1개
                 ; quote 제거를 해야함
```

위 문법에서 각각의 구성 요소(`pipe_sequence`, `simple_command` 등)는 각자의 생성 함수를 가진다. 예를 들어 `cmd_element`를 생성하는 함수는 `parse_cmd_element()`이다.

파서는 문법 체계에서 가장 상위에 있는 구성 요소를 먼저 생성하려 시도한다. 각 구성 요소는 그를 구성하는 하위 요소를 생성하려 시도한다. 위 표에서는 어떤 요소를 구성할 수 있는 하나의 가능성이 한 줄에 하나씩 기술되어 있다.

어떤 요소를 생성하는 함수는 기본적으로 모든 가능성을 차례대로 시험해본다. 예를 들어 `cmd_element`를 생성하는 함수는 첫번째 가능성 (`WORD` 하나)를 시험해보고 실패할 시 다음 가능성으로 넘어간다. 이때 어떤 가능성을 생성하는 데 성공했다면 다음 가능성은 확인해보지 않고 성공 판정을 내린다. 생성한 노드는 즉시 반환한다. 만약 도중에 오류가 발생한다면 다음으로 가능한 하위 요소들을 생성해본다. 모든 가능한 경우의 수가 실패한다면 해당 구성 요소는 이 토큰 배열에 존재하지 않는 것이다.

파서는 최상위 구성 요소 (`pipe_sequence`)를 생성하지 못했다면 토큰 배열 전체가 잘못된 것이라고 판단한다.

```
예시

io_redirect를 생성하는 함수:
	부모 노드를 하나 만든다.
	io_file을 생성해본다.
	생성이 잘 됐다면:
		부모 노드에 자식으로 추가하고 부모 노드를 반환한다.
	생성이 안됐다면 io_here를 생성해본다.
	생성이 잘 됐다면:
		부모 노드에 자식으로 추가하고 부모 노드를 반환한다.
	어떠한 것도 생성이 안됐다면 NULL을 반환한다.

io_file을 생성하는 함수:
	현재 토큰이 '<' '>' '>>' 중 하나인가?
		아니라면 io_file은 현재 위치에서 만들수 없다. NULL을 반환한다.
	현재 토큰을 하나 소모하여 부모 노드를 만든다.
	filename을 생성해본다.
	생성이 잘 됐다면:
		부모 노드에 자식으로 추가하고 부모 노드를 반환한다.
	생성이 안 됐다면 io_file은 현재 위치에서 만들수 없다. 토큰 포인터를 1 되감고 NULL을 반환한다.

filename을 생성하는 함수:
	현재 토큰이 WORD인가?
		아니라면 filename은 현재 위치에서 만들수 없다. NULL을 반환한다.
	현재 토큰을 하나 소모하여 부모 노드를 만든다.
	부모 노드를 반환한다.

...
```

파서는 일렬로 배열된 토큰을 차례대로 처리한다. `WORD`나 `'>>'`같이 토큰 1개와 1:1로 대응하는 요소를 파싱할 때는 해당하는 토큰을 하나씩 소모하게 된다. 이는 토큰의 포인터를 마련하고, 포인터를 첫번째 토큰에 맞추고, 토큰 하나를 소모할 때마다 포인터를 1 증가시키는 것으로 구현할 수 있다.

토큰을 소모하는 동작을 포인터로 구현하기 위해서는, 파싱 과정에서 하나의 가능성이 실패했을 때 증가시켜놓은 포인터를 되돌리는 작업이 필요하다. 각 노드는 자신이 생성되었을 당시 소모된 토큰의 수를 기록한다면 어떤 노드의 총 토큰 수는 부모 노드와 모든 자식 노드의 토큰 수를 합하여 구할 수 있다. 파싱 도중 어떤 가능성이 실패한다면 생성한 임시 노드들의 토큰 수를 합하여 그만큼 토큰 포인터를 감소시켜야 한다.

> 이 기능은 현재 구현되었지만 이 기능이 필요한 경우가 존재하지 않는다. 현재의 BNF 문법에서는 토큰을 소모한 상태에서 어떤 가능성이 실패한다면 그것은 파싱 실패를 의미하기 때문에 되감기가 발생하긴 하지만 유용하게 사용되지는 않는다.
>
> 추후 문법이 고도화된다면 이 기능은 반드시 필요하다.

파서는 내부적으로 다음과 같은 구조를 가진다.

```c
typedef struct s_parser
{
	t_token	*tok_start;
	t_token	*tok_curr;
	t_token	*tok_last;
	int		n_tokens;
}	t_parser;
```

`parse_tokens()`를 호출하면, 내부적으로 위 구조체에 필요한 정보를 초기화시킨 후 이를 참조하여 파싱이 진행된다. 이 구조체는 다음의 멤버를 가진다. 

- `t_token *tok_start`: 주어진 토큰 배열의 첫 주소
- `t_token *tok_curr`: 현재 파서가 바라보고 있는 토큰의 주소
- `t_token *tok_last`: 토큰 배열의 마지막 주소의 다음 주소
- `int n_tokens`: 주어진 토큰 배열의 크기

> 토큰이 5개 주어진다면 `n_tokens == 5` 이고 `tok_last == tok_start + 5` 이다.

파서는 `tok_curr`를 앞뒤로 이동시키며 파싱을 진행한다. 이때 현재 파서가 바라보는 토큰의 정보는 `tok_curr->type`과 같이 간단히 접근할 수 있다. 토큰 배열의 마지막에 도달하였는지 여부는 `tok_curr == tok_last`와 같이 조회할 수 있다.


## 각 함수 설명

아래에 설명하는 코드는 소스에서 발췌하였으나 로직에 직접적으로 연관되지 않았거나 예외 처리에 관련된 코드는 생략되어 있다.

### node_create

```c
// 노드를 할당하여 반환한다.
// n_tokens에는 반드시 이 노드를 생성할 때 소모한 토큰의 수를 넣는다.
// 예를 들어 io_redirect는 0, io_file은 1, filename은 1이다.
// pipe_sequence같은 경우는 파싱이 끝나야 토큰 수를 알 수 있으므로 생성시에는 0을 설정하고 추후 증가시킨다.
t_node	*node_create(int type, char *content, int n_tokens)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	/* 생략 */
	new_node->childs = ft_lstnew(NULL); // 자식 노드는 libft의 t_list로 구현
	/* 생략 */
	return (new_node);
}
```

### node_destroy

```c
static void	node_destroy_internal(void *root);

// 모든 자식 노드에 대해 destroy 함수를 재귀적으로 호출하고 마지막으로 본인을 할당 해제한다.
t_node	*node_destroy(t_node *node)
{
	if (!node) // 재귀의 끝에 도달함
		return (NULL);
	if (node->childs)
		ft_lstclear(&(node->childs), node_destroy_internal);
	if (node->content)
		free(node->content);
	free(node);
	return (NULL);
}
```

### node_addchild

```c
// node의 자식으로 child를 추가한다.
int	node_addchild(t_node *node, t_node *child);
```

### node_getntokens

```c
// 모든 자식의 토큰 개수를 재귀적으로 더하고 자신의 토큰 개수까지 더하여 반환한다.
int	node_getntokens(t_node *node)
{
	/* 생략 */
	n_tokens = node->n_tokens;
	cursor = node->childs;
	while (cursor)
	{
		n_tokens += node_getntokens(cursor->content);
		cursor = cursor->next;
	}
	return (n_tokens);
}
```

### parse_abort

```c
// 노드 생성 중 이를 중단해야 할 시 생성된 임시 노드를 root와 child에 입력한다.
// 생성하지 않았을 시 NULL을 입력한다.
t_node	*parse_abort(t_parser *parser, t_node *root, t_node *child)
{
	int	rewind_counter;

	rewind_counter = 0;
	if (root)
	{
		rewind_counter += node_getntokens(root);
		node_destroy(root);
	}
	if (child)
	{
		rewind_counter += node_getntokens(child);
		node_destroy(child);
	}
	parser->tok_curr -= rewind_counter; // 토큰 포인터 되감기
	return (NULL);
}
```

### parse_here_end

```c
// parse_filename과 비슷하게 동작한다.
t_node	*parse_here_end(t_parser *parser);
```

### parse_filename

```c
t_node	*parse_filename(t_parser *parser)
{
	if (parser_is_last_token(parser)) // 마지막 토큰에 도달했다면 더 이상 파싱할 수 없다.
		return (NULL);
	if (parser->tok_curr->type != TOKENTYPE_WORD) // 현재 토큰이 WORD가 아니라면 파싱할 수 없다.
		return (NULL);
	// 타입이 FILENAME, 콘텐트가 현재 토큰의 콘텐츠이고 토큰을 1개 소모하는 노드 생성
	root = node_create(NODETYPE_FILENAME, parser->tok_curr->content, 1);
	parser->tok_curr++; // 토큰을 1개 소모
	return (root);
}
```

### parse_io_here

```c
// << 토큰을 하나 소모하여 root를 만들고 child로 here_end를 추가한다.
// parse_io_file과 비슷하게 동작한다.
t_node	*parse_io_here(t_parser *parser);
```

### parse_io_file

```c
// 마지막 토큰에 도달했다면 더 이상 파싱할 수 없다.
// 현재 토큰의 타입이 <, >, >>이 아니라면 파싱할 수 없다.
static int	can_parse_io_file(t_parser *parser)
{
	if (parser_is_last_token(parser))
		return (FALSE);
	if (parser->tok_curr->type == TOKENTYPE_REDIR_IN)
		return (TRUE);
	if (parser->tok_curr->type == TOKENTYPE_REDIR_OUT)
		return (TRUE);
	if (parser->tok_curr->type == TOKENTYPE_REDIR_OUT_APPEND)
		return (TRUE);
	return (FALSE);
}

t_node	*parse_io_file(t_parser *parser)
{
	if (!can_parse_io_file(parser)) // 위에서 정의한 조건에 맞아야 파싱할 수 있다.
		return (NULL);
	// 타입이 NODETYPE_IO_FILE, 콘텐트가 현재 토큰의 콘텐츠이고 토큰을 1개 소모하는 노드 생성
	root = node_create(NODETYPE_IO_FILE, parser->tok_curr->content, 1);
	parser->tok_curr++; // 토큰을 1개 소모
	child = parse_filename(parser); // 다음 요소는 filename이어야 한다.
	if (!child) // filename을 생성하지 못했다면 io_file도 생성할 수 없다.
		return (parse_abort(parser, root, NULL)); // root가 소모한 토큰을 되감기하고 파싱을 취소한다.
	// filename을 생성했다면 io_file을 생성하는 데 성공한 것이다.
	node_addchild(root, child); // filename을 io_file의 자식으로 추가한다.
	return (root);
}
```

### parse_io_redirect

```c
t_node	*parse_io_redirect(t_parser *parser)
{
	if (parser_is_last_token(parser)) // 마지막 토큰에 도달했다면 더 이상 파싱할 수 없다.
		return (NULL);
	root = node_create(NODETYPE_IO_REDIRECT, "", 0); // 이 구성 요소는 직접 토큰을 소모하지는 않는다.
	child = parse_io_file(parser); // io_file을 생성해본다.
	if (child)
	{
		node_addchild(root, child);
		return (root);
	}
	child = parse_io_here(parser); // 안되면 io_here를 생성해본다.
	if (child)
	{
		node_addchild(root, child);
		return (root);
	}
	return (parse_abort(parser, root, NULL)); // 되는 경우가 없으므로 파싱을 취소한다.
}
```

### parse_cmd_element

```c
t_node	*parse_cmd_element(t_parser *parser)
{
	if (parser_is_last_token(parser))
		return (NULL);
	if (parser->tok_curr->type == TOKENTYPE_WORD) // 현재 토큰이 WORD라면
	{	// 현재 토큰을 소모하여 root에 담고 종료한다.
		root = node_create(NODETYPE_CMD_ELEMENT, parser->tok_curr->content, 1);
		parser->tok_curr++;
		return (root);
	}
	root = node_create(NODETYPE_CMD_ELEMENT, "", 0); // 현재 토큰이 WORD가 아니라면
	child = parse_io_redirect(parser); // io_redirect를 root에 담아 반환한다.
	if (!child)
		return (parse_abort(parser, root, NULL)); // io_redirect가 생성되지 않았다면 cmd_element 생성 실패다.
	node_addchild(root, child);
	return (root);
}
```

### parse_simple_command

```c
t_node	*parse_simple_command(t_parser *parser)
{
	if (parser_is_last_token(parser))
		return (NULL);
	root = node_create(NODETYPE_SIMPLE_COMMAND, "", 0); // simple_command는 직접 소모하는 토큰이 없다.
	while (TRUE) // greedy하게 하위 요소 생성을 계속한다.
	{
		child = parse_cmd_element(parser);
		if (!child) // 루프를 돌던 중 child 생성에 실패했다.
		{
			if (node_getntokens(root)) // root에 토큰이 1개라도 담겨있던 경우
				return (root); // 지금까지 생성한 노드를 반환한다.
			// root에 토큰이 1개도 없는 경우 simple_command 생성에 실패한 것이다.
			return (parse_abort(parser, root, NULL));
		}
		node_addchild(root, child);
	}
}
```

### parse_pipe_sequence

```c
static int	can_parse_pipe_sequence(t_parser *parser)
{
	if (parser_is_last_token(parser))
		return (FALSE);
	if (parser->tok_curr->type == TOKENTYPE_PIPE)
		return (FALSE);
	return (TRUE);
}

t_node	*parse_pipe_sequence(t_parser *parser)
{
	if (!can_parse_pipe_sequence(parser))
		return (NULL);
	root = node_create(NODETYPE_PIPE_SEQUENCE, "", 0);
	while (TRUE) // greedy하게 하위 요소 생성을 계속한다.
	{
		child = parse_simple_command(parser);
		if (!child) // simple_command 생성에 실패 시 전체 토큰 배열이 잘못된 것이다.
			return (parse_abort(parser, root, NULL));
		node_addchild(root, child);
		if (parser_is_last_token(parser)) // simple_command를 생성하자 토큰이 전부 소모되었다.
			return (root); // 전체 토큰 배열이 잘 파싱 되었다.
		if (parser->tok_curr->type != TOKENTYPE_PIPE) // simple_command를 생성했는데 다음 토큰이 파이프가 아니다. 즉 남은 토큰이 있다.
			return (parse_abort(parser, root, NULL)); // 전체 토큰 배열이 잘못된 것이다.
		parser->tok_curr++; // 토큰 하나 ('|')를 소모한다.
		root->n_tokens++; // pipe_sequence가 소모한 토큰 개수가 늘어난다.
	}
}
```

### parse_tokens

```c
// 파서가 사용하는 포인터를 초기화시키고 최상위 노드 생성 함수를 호출한다.
t_node	*parse_tokens(t_token *tokenarr, int n_tokens)
{
	t_parser	parser;

	parser.tok_start = tokenarr;
	parser.tok_curr = tokenarr;
	parser.tok_last = tokenarr + n_tokens;
	parser.n_tokens = n_tokens;
	return (parse_pipe_sequence(&parser));
}
```
