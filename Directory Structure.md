```
ROOT
├── modules
│   ├── libft
│   ├── libmodule1
│   └── libmodule2
├── includes
│   └── *.h
├── srcs
│   └── *.c
└── Makefile
```

module 디렉토리 안에 각 모듈을 배치한다. 모듈로 분류될 수 없는 기능은 ROOT/srcs 및 ROOT/includes에 배치한다. 

```
libmodule1
├── includes
│   └── *.h
├── srcs
│   ├── *.c
│   └── *.h
├── *.c
├── *.h
└── Makefile
```

각 모듈은 독자적인 Makefile을 가지고 있고, 여기서는 libft와 같이 파일을 컴파일 및 아카이빙만 할 뿐 링크를 수행하지 않는다. 

타 모듈에서 사용해야 하는 함수 및 구조체는 includes 내에 정의한다. 이 모듈 내에서만 사용되는 내용은 includes에 노출시키지 않는다.
