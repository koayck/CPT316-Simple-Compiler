// Generated from c:/Users/User/Desktop/USM/Y3/CPT316/Assignment/CPT316-Simple-Compiler/MiniLang.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue", "this-escape"})
public class MiniLangLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, IDENTIFIER=6, INTEGER=7, DOUBLE=8, 
		STRING=9, BOOLEAN=10, TYPE_INT=11, TYPE_DOUBLE=12, TYPE_STRING=13, TYPE_BOOL=14, 
		PLUS=15, MINUS=16, MULTIPLY=17, DIVIDE=18, POWER=19, ASSIGN=20, GREATER=21, 
		LESS=22, GREATER_EQUAL=23, LESS_EQUAL=24, EQUAL_EQUAL=25, NOT_EQUAL=26, 
		AND=27, OR=28, NOT=29, LPAREN=30, RPAREN=31, LBRACE=32, RBRACE=33, SEMICOLON=34;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"T__0", "T__1", "T__2", "T__3", "T__4", "IDENTIFIER", "INTEGER", "DOUBLE", 
			"STRING", "BOOLEAN", "TYPE_INT", "TYPE_DOUBLE", "TYPE_STRING", "TYPE_BOOL", 
			"PLUS", "MINUS", "MULTIPLY", "DIVIDE", "POWER", "ASSIGN", "GREATER", 
			"LESS", "GREATER_EQUAL", "LESS_EQUAL", "EQUAL_EQUAL", "NOT_EQUAL", "AND", 
			"OR", "NOT", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "SEMICOLON"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'p'", "'r'", "'if'", "'else'", "'while'", null, null, null, null, 
			null, "'int'", "'double'", "'string'", "'bool'", "'+'", "'-'", "'*'", 
			"'/'", "'**'", "'='", "'>'", "'<'", "'>='", "'<='", "'=='", "'!='", "'&&'", 
			"'||'", "'!'", "'('", "')'", "'{'", "'}'", "';'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, "IDENTIFIER", "INTEGER", "DOUBLE", 
			"STRING", "BOOLEAN", "TYPE_INT", "TYPE_DOUBLE", "TYPE_STRING", "TYPE_BOOL", 
			"PLUS", "MINUS", "MULTIPLY", "DIVIDE", "POWER", "ASSIGN", "GREATER", 
			"LESS", "GREATER_EQUAL", "LESS_EQUAL", "EQUAL_EQUAL", "NOT_EQUAL", "AND", 
			"OR", "NOT", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "SEMICOLON"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}


	public MiniLangLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "MiniLang.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\u0004\u0000\"\u00c8\u0006\uffff\uffff\u0002\u0000\u0007\u0000\u0002\u0001"+
		"\u0007\u0001\u0002\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004"+
		"\u0007\u0004\u0002\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007"+
		"\u0007\u0007\u0002\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002\u000b"+
		"\u0007\u000b\u0002\f\u0007\f\u0002\r\u0007\r\u0002\u000e\u0007\u000e\u0002"+
		"\u000f\u0007\u000f\u0002\u0010\u0007\u0010\u0002\u0011\u0007\u0011\u0002"+
		"\u0012\u0007\u0012\u0002\u0013\u0007\u0013\u0002\u0014\u0007\u0014\u0002"+
		"\u0015\u0007\u0015\u0002\u0016\u0007\u0016\u0002\u0017\u0007\u0017\u0002"+
		"\u0018\u0007\u0018\u0002\u0019\u0007\u0019\u0002\u001a\u0007\u001a\u0002"+
		"\u001b\u0007\u001b\u0002\u001c\u0007\u001c\u0002\u001d\u0007\u001d\u0002"+
		"\u001e\u0007\u001e\u0002\u001f\u0007\u001f\u0002 \u0007 \u0002!\u0007"+
		"!\u0001\u0000\u0001\u0000\u0001\u0001\u0001\u0001\u0001\u0002\u0001\u0002"+
		"\u0001\u0002\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003"+
		"\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004"+
		"\u0001\u0005\u0001\u0005\u0005\u0005Z\b\u0005\n\u0005\f\u0005]\t\u0005"+
		"\u0001\u0006\u0004\u0006`\b\u0006\u000b\u0006\f\u0006a\u0001\u0007\u0004"+
		"\u0007e\b\u0007\u000b\u0007\f\u0007f\u0001\u0007\u0001\u0007\u0004\u0007"+
		"k\b\u0007\u000b\u0007\f\u0007l\u0001\b\u0001\b\u0005\bq\b\b\n\b\f\bt\t"+
		"\b\u0001\b\u0001\b\u0001\t\u0001\t\u0001\t\u0001\t\u0001\t\u0001\t\u0001"+
		"\t\u0001\t\u0001\t\u0003\t\u0081\b\t\u0001\n\u0001\n\u0001\n\u0001\n\u0001"+
		"\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001"+
		"\u000b\u0001\f\u0001\f\u0001\f\u0001\f\u0001\f\u0001\f\u0001\f\u0001\r"+
		"\u0001\r\u0001\r\u0001\r\u0001\r\u0001\u000e\u0001\u000e\u0001\u000f\u0001"+
		"\u000f\u0001\u0010\u0001\u0010\u0001\u0011\u0001\u0011\u0001\u0012\u0001"+
		"\u0012\u0001\u0012\u0001\u0013\u0001\u0013\u0001\u0014\u0001\u0014\u0001"+
		"\u0015\u0001\u0015\u0001\u0016\u0001\u0016\u0001\u0016\u0001\u0017\u0001"+
		"\u0017\u0001\u0017\u0001\u0018\u0001\u0018\u0001\u0018\u0001\u0019\u0001"+
		"\u0019\u0001\u0019\u0001\u001a\u0001\u001a\u0001\u001a\u0001\u001b\u0001"+
		"\u001b\u0001\u001b\u0001\u001c\u0001\u001c\u0001\u001d\u0001\u001d\u0001"+
		"\u001e\u0001\u001e\u0001\u001f\u0001\u001f\u0001 \u0001 \u0001!\u0001"+
		"!\u0000\u0000\"\u0001\u0001\u0003\u0002\u0005\u0003\u0007\u0004\t\u0005"+
		"\u000b\u0006\r\u0007\u000f\b\u0011\t\u0013\n\u0015\u000b\u0017\f\u0019"+
		"\r\u001b\u000e\u001d\u000f\u001f\u0010!\u0011#\u0012%\u0013\'\u0014)\u0015"+
		"+\u0016-\u0017/\u00181\u00193\u001a5\u001b7\u001c9\u001d;\u001e=\u001f"+
		"? A!C\"\u0001\u0000\u0004\u0003\u0000AZ__az\u0004\u000009AZ__az\u0001"+
		"\u000009\u0003\u0000\n\n\r\r\"\"\u00cd\u0000\u0001\u0001\u0000\u0000\u0000"+
		"\u0000\u0003\u0001\u0000\u0000\u0000\u0000\u0005\u0001\u0000\u0000\u0000"+
		"\u0000\u0007\u0001\u0000\u0000\u0000\u0000\t\u0001\u0000\u0000\u0000\u0000"+
		"\u000b\u0001\u0000\u0000\u0000\u0000\r\u0001\u0000\u0000\u0000\u0000\u000f"+
		"\u0001\u0000\u0000\u0000\u0000\u0011\u0001\u0000\u0000\u0000\u0000\u0013"+
		"\u0001\u0000\u0000\u0000\u0000\u0015\u0001\u0000\u0000\u0000\u0000\u0017"+
		"\u0001\u0000\u0000\u0000\u0000\u0019\u0001\u0000\u0000\u0000\u0000\u001b"+
		"\u0001\u0000\u0000\u0000\u0000\u001d\u0001\u0000\u0000\u0000\u0000\u001f"+
		"\u0001\u0000\u0000\u0000\u0000!\u0001\u0000\u0000\u0000\u0000#\u0001\u0000"+
		"\u0000\u0000\u0000%\u0001\u0000\u0000\u0000\u0000\'\u0001\u0000\u0000"+
		"\u0000\u0000)\u0001\u0000\u0000\u0000\u0000+\u0001\u0000\u0000\u0000\u0000"+
		"-\u0001\u0000\u0000\u0000\u0000/\u0001\u0000\u0000\u0000\u00001\u0001"+
		"\u0000\u0000\u0000\u00003\u0001\u0000\u0000\u0000\u00005\u0001\u0000\u0000"+
		"\u0000\u00007\u0001\u0000\u0000\u0000\u00009\u0001\u0000\u0000\u0000\u0000"+
		";\u0001\u0000\u0000\u0000\u0000=\u0001\u0000\u0000\u0000\u0000?\u0001"+
		"\u0000\u0000\u0000\u0000A\u0001\u0000\u0000\u0000\u0000C\u0001\u0000\u0000"+
		"\u0000\u0001E\u0001\u0000\u0000\u0000\u0003G\u0001\u0000\u0000\u0000\u0005"+
		"I\u0001\u0000\u0000\u0000\u0007L\u0001\u0000\u0000\u0000\tQ\u0001\u0000"+
		"\u0000\u0000\u000bW\u0001\u0000\u0000\u0000\r_\u0001\u0000\u0000\u0000"+
		"\u000fd\u0001\u0000\u0000\u0000\u0011n\u0001\u0000\u0000\u0000\u0013\u0080"+
		"\u0001\u0000\u0000\u0000\u0015\u0082\u0001\u0000\u0000\u0000\u0017\u0086"+
		"\u0001\u0000\u0000\u0000\u0019\u008d\u0001\u0000\u0000\u0000\u001b\u0094"+
		"\u0001\u0000\u0000\u0000\u001d\u0099\u0001\u0000\u0000\u0000\u001f\u009b"+
		"\u0001\u0000\u0000\u0000!\u009d\u0001\u0000\u0000\u0000#\u009f\u0001\u0000"+
		"\u0000\u0000%\u00a1\u0001\u0000\u0000\u0000\'\u00a4\u0001\u0000\u0000"+
		"\u0000)\u00a6\u0001\u0000\u0000\u0000+\u00a8\u0001\u0000\u0000\u0000-"+
		"\u00aa\u0001\u0000\u0000\u0000/\u00ad\u0001\u0000\u0000\u00001\u00b0\u0001"+
		"\u0000\u0000\u00003\u00b3\u0001\u0000\u0000\u00005\u00b6\u0001\u0000\u0000"+
		"\u00007\u00b9\u0001\u0000\u0000\u00009\u00bc\u0001\u0000\u0000\u0000;"+
		"\u00be\u0001\u0000\u0000\u0000=\u00c0\u0001\u0000\u0000\u0000?\u00c2\u0001"+
		"\u0000\u0000\u0000A\u00c4\u0001\u0000\u0000\u0000C\u00c6\u0001\u0000\u0000"+
		"\u0000EF\u0005p\u0000\u0000F\u0002\u0001\u0000\u0000\u0000GH\u0005r\u0000"+
		"\u0000H\u0004\u0001\u0000\u0000\u0000IJ\u0005i\u0000\u0000JK\u0005f\u0000"+
		"\u0000K\u0006\u0001\u0000\u0000\u0000LM\u0005e\u0000\u0000MN\u0005l\u0000"+
		"\u0000NO\u0005s\u0000\u0000OP\u0005e\u0000\u0000P\b\u0001\u0000\u0000"+
		"\u0000QR\u0005w\u0000\u0000RS\u0005h\u0000\u0000ST\u0005i\u0000\u0000"+
		"TU\u0005l\u0000\u0000UV\u0005e\u0000\u0000V\n\u0001\u0000\u0000\u0000"+
		"W[\u0007\u0000\u0000\u0000XZ\u0007\u0001\u0000\u0000YX\u0001\u0000\u0000"+
		"\u0000Z]\u0001\u0000\u0000\u0000[Y\u0001\u0000\u0000\u0000[\\\u0001\u0000"+
		"\u0000\u0000\\\f\u0001\u0000\u0000\u0000][\u0001\u0000\u0000\u0000^`\u0007"+
		"\u0002\u0000\u0000_^\u0001\u0000\u0000\u0000`a\u0001\u0000\u0000\u0000"+
		"a_\u0001\u0000\u0000\u0000ab\u0001\u0000\u0000\u0000b\u000e\u0001\u0000"+
		"\u0000\u0000ce\u0007\u0002\u0000\u0000dc\u0001\u0000\u0000\u0000ef\u0001"+
		"\u0000\u0000\u0000fd\u0001\u0000\u0000\u0000fg\u0001\u0000\u0000\u0000"+
		"gh\u0001\u0000\u0000\u0000hj\u0005.\u0000\u0000ik\u0007\u0002\u0000\u0000"+
		"ji\u0001\u0000\u0000\u0000kl\u0001\u0000\u0000\u0000lj\u0001\u0000\u0000"+
		"\u0000lm\u0001\u0000\u0000\u0000m\u0010\u0001\u0000\u0000\u0000nr\u0005"+
		"\"\u0000\u0000oq\b\u0003\u0000\u0000po\u0001\u0000\u0000\u0000qt\u0001"+
		"\u0000\u0000\u0000rp\u0001\u0000\u0000\u0000rs\u0001\u0000\u0000\u0000"+
		"su\u0001\u0000\u0000\u0000tr\u0001\u0000\u0000\u0000uv\u0005\"\u0000\u0000"+
		"v\u0012\u0001\u0000\u0000\u0000wx\u0005t\u0000\u0000xy\u0005r\u0000\u0000"+
		"yz\u0005u\u0000\u0000z\u0081\u0005e\u0000\u0000{|\u0005f\u0000\u0000|"+
		"}\u0005a\u0000\u0000}~\u0005l\u0000\u0000~\u007f\u0005s\u0000\u0000\u007f"+
		"\u0081\u0005e\u0000\u0000\u0080w\u0001\u0000\u0000\u0000\u0080{\u0001"+
		"\u0000\u0000\u0000\u0081\u0014\u0001\u0000\u0000\u0000\u0082\u0083\u0005"+
		"i\u0000\u0000\u0083\u0084\u0005n\u0000\u0000\u0084\u0085\u0005t\u0000"+
		"\u0000\u0085\u0016\u0001\u0000\u0000\u0000\u0086\u0087\u0005d\u0000\u0000"+
		"\u0087\u0088\u0005o\u0000\u0000\u0088\u0089\u0005u\u0000\u0000\u0089\u008a"+
		"\u0005b\u0000\u0000\u008a\u008b\u0005l\u0000\u0000\u008b\u008c\u0005e"+
		"\u0000\u0000\u008c\u0018\u0001\u0000\u0000\u0000\u008d\u008e\u0005s\u0000"+
		"\u0000\u008e\u008f\u0005t\u0000\u0000\u008f\u0090\u0005r\u0000\u0000\u0090"+
		"\u0091\u0005i\u0000\u0000\u0091\u0092\u0005n\u0000\u0000\u0092\u0093\u0005"+
		"g\u0000\u0000\u0093\u001a\u0001\u0000\u0000\u0000\u0094\u0095\u0005b\u0000"+
		"\u0000\u0095\u0096\u0005o\u0000\u0000\u0096\u0097\u0005o\u0000\u0000\u0097"+
		"\u0098\u0005l\u0000\u0000\u0098\u001c\u0001\u0000\u0000\u0000\u0099\u009a"+
		"\u0005+\u0000\u0000\u009a\u001e\u0001\u0000\u0000\u0000\u009b\u009c\u0005"+
		"-\u0000\u0000\u009c \u0001\u0000\u0000\u0000\u009d\u009e\u0005*\u0000"+
		"\u0000\u009e\"\u0001\u0000\u0000\u0000\u009f\u00a0\u0005/\u0000\u0000"+
		"\u00a0$\u0001\u0000\u0000\u0000\u00a1\u00a2\u0005*\u0000\u0000\u00a2\u00a3"+
		"\u0005*\u0000\u0000\u00a3&\u0001\u0000\u0000\u0000\u00a4\u00a5\u0005="+
		"\u0000\u0000\u00a5(\u0001\u0000\u0000\u0000\u00a6\u00a7\u0005>\u0000\u0000"+
		"\u00a7*\u0001\u0000\u0000\u0000\u00a8\u00a9\u0005<\u0000\u0000\u00a9,"+
		"\u0001\u0000\u0000\u0000\u00aa\u00ab\u0005>\u0000\u0000\u00ab\u00ac\u0005"+
		"=\u0000\u0000\u00ac.\u0001\u0000\u0000\u0000\u00ad\u00ae\u0005<\u0000"+
		"\u0000\u00ae\u00af\u0005=\u0000\u0000\u00af0\u0001\u0000\u0000\u0000\u00b0"+
		"\u00b1\u0005=\u0000\u0000\u00b1\u00b2\u0005=\u0000\u0000\u00b22\u0001"+
		"\u0000\u0000\u0000\u00b3\u00b4\u0005!\u0000\u0000\u00b4\u00b5\u0005=\u0000"+
		"\u0000\u00b54\u0001\u0000\u0000\u0000\u00b6\u00b7\u0005&\u0000\u0000\u00b7"+
		"\u00b8\u0005&\u0000\u0000\u00b86\u0001\u0000\u0000\u0000\u00b9\u00ba\u0005"+
		"|\u0000\u0000\u00ba\u00bb\u0005|\u0000\u0000\u00bb8\u0001\u0000\u0000"+
		"\u0000\u00bc\u00bd\u0005!\u0000\u0000\u00bd:\u0001\u0000\u0000\u0000\u00be"+
		"\u00bf\u0005(\u0000\u0000\u00bf<\u0001\u0000\u0000\u0000\u00c0\u00c1\u0005"+
		")\u0000\u0000\u00c1>\u0001\u0000\u0000\u0000\u00c2\u00c3\u0005{\u0000"+
		"\u0000\u00c3@\u0001\u0000\u0000\u0000\u00c4\u00c5\u0005}\u0000\u0000\u00c5"+
		"B\u0001\u0000\u0000\u0000\u00c6\u00c7\u0005;\u0000\u0000\u00c7D\u0001"+
		"\u0000\u0000\u0000\u0007\u0000[aflr\u0080\u0000";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}