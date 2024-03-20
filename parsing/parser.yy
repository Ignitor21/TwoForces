%language "c++"
%skeleton "lalr1.cc" 
%require "3.5.2"
%defines

%define api.token.constructor
%define api.value.type variant
%define api.token.raw
%define parse.assert

%code requires
{
    #include <string>
    #include <unordered_map>
    #include "ast.hxx"
    using namespace frontend;
}

%parse-param { ast& abs_syntax_tree }
%param { yy::location& loc}
%locations

%define parse.trace
%define parse.error verbose

%code 
{
    #include "driver.hxx"
}   

%token
  END  0  "end of file"
  ASGN      "="
  PLUS      "+"
  MINUS     "-"
  MUL       "*"
  DIV       "/"
  MOD       "%"
  LPAREN    "("
  RPAREN    ")"
  LBRACE    "{"
  RBRACE    "}"
  SCOLON    ";"
  IF        "if"
  ELSE      "else"
  WHILE     "while" 
  PRINT     "print"
  INPUT     "?"

  LESS      "<"
  GREATER   ">"
  EQ        "=="
  NEQ       "!="
  LESSEQ    "<="
  GREATEREQ ">="
  AND       "&&"
  OR        "||"
  NOT       "!"
;

%token <std::string> ID
%token <int> NUMBER

%nterm program
%nterm <scope*> stmts
%nterm <scope*> scope
%nterm <scope*> right_brace
%nterm <INode*> stmt
%nterm <assignment_expression*> assignment 
%nterm <output_statement*> output
%nterm <if_statement*> fork
%nterm <while_statement*> loop
%nterm <INode*> body
%nterm <identificator_expression*> lval
%nterm <expression*> expr term

%precedence ")"
%precedence "else"

%right "=";
%left "||";
%left "&&";
%nonassoc "==" "!=";
%nonassoc "<" "<=" ">" ">="
%left "+" "-";
%left "*" "/" "%"
%right "!"

%printer { yyo << $$; } <*>;

%%

program: stmts { abs_syntax_tree.execute(); } 

stmts: 
  %empty      {}  
| stmts ";"   {}
| stmts stmt  { abs_syntax_tree.add_action($2); }
| stmts scope { abs_syntax_tree.add_action($2); }
;

stmt: 
  assignment ";" { $$ = $1; }
| output     ";" { $$ = $1; }
| fork           { $$ = $1; }
| loop           { $$ = $1; }
;

assignment:
  lval "=" expr { $$ = abs_syntax_tree.create_node(assignment_expression(@2, $1, $3));
                    abs_syntax_tree.current_scope_->add_id($1->get_name(), $1); }
;

lval:
  ID            { identificator_expression* ret = abs_syntax_tree.current_scope_->get($1);

                  if (ret)
                      $$ =  ret;
                  else
                      $$ = abs_syntax_tree.create_node(identificator_expression(@1, $1)); } 
;

output:
  "print" expr  { $$ = abs_syntax_tree.create_node(output_statement(@1, $2)); }
;

fork:
  "if" "(" expr ")" body             { $$ = abs_syntax_tree.create_node(if_statement(@1, $3, $5));     }
| "if" "(" expr ")" body "else" body { $$ = abs_syntax_tree.create_node(if_statement(@1, $3, $5, $7)); }
;

loop:
  "while" "(" expr ")" body { $$ = abs_syntax_tree.create_node(while_statement(@1, $3, $5)); }
;

body:
  scope { $$ = $1; }
| stmt  { $$ = $1; } 
;

scope:
    left_brace stmts right_brace { $$ = $3; }
;    

left_brace:
  "{" { abs_syntax_tree.current_scope_ = abs_syntax_tree.create_node(scope(abs_syntax_tree.current_scope_)); } 
;

right_brace:
  "}" { $$ = abs_syntax_tree.current_scope_; abs_syntax_tree.reset_scope(); }
;

expr:
  expr "+"  expr { $$ = abs_syntax_tree.create_node(binary_op_expression(@2, $1, BinOps::PLUS,      $3));              }
| expr "-"  expr { $$ = abs_syntax_tree.create_node(binary_op_expression(@2, $1, BinOps::MINUS,     $3));              } 
| expr "*"  expr { $$ = abs_syntax_tree.create_node(binary_op_expression(@2, $1, BinOps::MUL,       $3));              }
| expr "/"  expr { $$ = abs_syntax_tree.create_node(binary_op_expression(@2, $1, BinOps::DIV,       $3));              }
| expr "%"  expr { $$ = abs_syntax_tree.create_node(binary_op_expression(@2, $1, BinOps::MOD,       $3));              }
| expr "<"  expr { $$ = abs_syntax_tree.create_node(binary_op_expression(@2, $1, BinOps::LESS,      $3));              }
| expr "<=" expr { $$ = abs_syntax_tree.create_node(binary_op_expression(@2, $1, BinOps::LESSEQ,    $3));              }
| expr ">"  expr { $$ = abs_syntax_tree.create_node(binary_op_expression(@2, $1, BinOps::GREATER,   $3));              }
| expr ">=" expr { $$ = abs_syntax_tree.create_node(binary_op_expression(@2, $1, BinOps::GREATEREQ, $3));              }
| expr "==" expr { $$ = abs_syntax_tree.create_node(binary_op_expression(@2, $1, BinOps::EQ,  $3));                    }
| expr "!=" expr { $$ = abs_syntax_tree.create_node(binary_op_expression(@2, $1, BinOps::NEQ, $3));                    }
| expr "&&" expr { $$ = abs_syntax_tree.create_node(binary_op_expression(@2, $1, BinOps::AND, $3));                    }
| expr "||" expr { $$ = abs_syntax_tree.create_node(binary_op_expression(@2, $1, BinOps::OR,  $3));                    }
| "!" expr       { $$ = abs_syntax_tree.create_node(unary_op_expression(@1, UnOps::NOT,    $2));                       }
| "+" term       { $$ = abs_syntax_tree.create_node(unary_op_expression(@1, UnOps::UPLUS,  $2));                       }
| "-" term       { $$ = abs_syntax_tree.create_node(unary_op_expression(@1, UnOps::UMINUS, $2));                       }
| term           { $$ = $1;                                                                                            }
| assignment     { $$ = $1;                                                                                            }
;

term:
  NUMBER         { $$ = abs_syntax_tree.create_node(number_expression(@1, $1));                                        }
| ID             { $$ = abs_syntax_tree.get_access(@1, $1);                                                            }
| "?"            { $$ = abs_syntax_tree.create_node(input_expression(@1));                                             }
| "(" expr ")"   { $$ = $2;                                                                                            }

%%

void yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
