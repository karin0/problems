//Pascal

type
	pointer_32=^longint;
var
	_IO_c:longint;
	seed:Cardinal;
	p:array[0..2000004]of longint;
	T,m,a,b,d,i:longint;
	ans_sum,cur_ans:Cardinal;

function randnum():Cardinal;
begin
	seed:=seed xor (seed shl 13);
	seed:=seed xor (seed shr 17);
	seed:=seed xor (seed shl 5);
	exit(seed);
end;

procedure init_case(var m,a,b,d:longint;p:pointer_32);inline;
var
	i:longint;
begin
	read(m,seed,a,b,_IO_c,d);
	for i:=1 to m do begin
		if randnum() mod _IO_c=0 then p[i]:=-1
		else p[i]:=randnum() mod b;
	end;
end;

procedure update_ans(var ans_sum:Cardinal;cur_ans:Cardinal;no:longint);inline;
const
	mod_val:Cardinal=998244353;
	calc:int64=1;
begin
	ans_sum:=ans_sum xor (calc*no*(no+7) mod mod_val*cur_ans mod mod_val);
end;

{
一开始请调用read(T)读入数据组数T
接下来每组数据开始时请调用init_case(m,a,b,d,p)读入m,a,b,d,p[]
每组数据开始时请用一个初始化为0的32位无符号整形变量ans_sum存储答案，然后对于每个i，
用32位无符号整形变量cur_ans存储第i次答案，并调用update_ans(ans_sum,cur_ans,i)更新。最后输出ans_sum即可。
}

//示例代码：
{
begin
	read(T);
	while T>0 do begin
		dec(T);
		ans_sum:=0;cur_ans:=0;
		init_case(m,a,b,d,p);
		for i:=1 to m do begin
			......//处理操作
			update_ans(ans_sum,cur_ans,i);
		end;
		writeln(ans_sum);
	end;
end.
}