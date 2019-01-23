//
//  MUHookMacro.h
//
//  Created by Magic-Unique on 2017/2/9.
//
//  Copyright Magic-Unique 2017
//

/**
 * Executes one or more expressions (which may have a void type, such as a call
 * to a function that returns no value) and always returns true.
 */
#define muhmacro_exprify(...) \
    ((__VA_ARGS__), true)

/**
 * Returns a string representation of VALUE after full macro expansion.
 */
#define muhmacro_stringify(VALUE) \
        muhmacro_stringify_(VALUE)

/**
 * Returns A and B concatenated after full macro expansion.
 */
#define muhmacro_concat(A, B) \
        muhmacro_concat_(A, B)

/**
 * Returns the Nth variadic argument (starting from zero). At least
 * N + 1 variadic arguments must be given. N must be between zero and twenty,
 * inclusive.
 */
#define muhmacro_at(N, ...) \
        muhmacro_concat(muhmacro_at, N)(__VA_ARGS__)

/**
 * Returns the number of arguments (up to twenty) provided to the macro. At
 * least one argument must be provided.
 *
 * Inspired by P99: http://p99.gforge.inria.fr
 */
#define muhmacro_argcount(...) \
        muhmacro_at(20, __VA_ARGS__, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)

/**
 * Identical to #muhmacro_foreach_cxt, except that no CONTEXT argument is
 * given. Only the index and current argument will thus be passed to MACRO.
 */
#define muhmacro_foreach(MACRO, SEP, ...) \
        muhmacro_foreach_cxt(muhmacro_foreach_iter, SEP, MACRO, __VA_ARGS__)

/**
 * For each consecutive variadic argument (up to twenty), MACRO is passed the
 * zero-based index of the current argument, CONTEXT, and then the argument
 * itself. The results of adjoining invocations of MACRO are then separated by
 * SEP.
 *
 * Inspired by P99: http://p99.gforge.inria.fr
 */
#define muhmacro_foreach_cxt(MACRO, SEP, CONTEXT, ...) \
        muhmacro_concat(muhmacro_foreach_cxt, muhmacro_argcount(__VA_ARGS__))(MACRO, SEP, CONTEXT, __VA_ARGS__)

/**
 * Identical to #muhmacro_foreach_cxt. This can be used when the former would
 * fail due to recursive macro expansion.
 */
#define muhmacro_foreach_cxt_recursive(MACRO, SEP, CONTEXT, ...) \
        muhmacro_concat(muhmacro_foreach_cxt_recursive, muhmacro_argcount(__VA_ARGS__))(MACRO, SEP, CONTEXT, __VA_ARGS__)

/**
 * In consecutive order, appends each variadic argument (up to twenty) onto
 * BASE. The resulting concatenations are then separated by SEP.
 *
 * This is primarily useful to manipulate a list of macro invocations into instead
 * invoking a different, possibly related macro.
 */
#define muhmacro_foreach_concat(BASE, SEP, ...) \
        muhmacro_foreach_cxt(muhmacro_foreach_concat_iter, SEP, BASE, __VA_ARGS__)

/**
 * Iterates COUNT times, each time invoking MACRO with the current index
 * (starting at zero) and CONTEXT. The results of adjoining invocations of MACRO
 * are then separated by SEP.
 *
 * COUNT must be an integer between zero and twenty, inclusive.
 */
#define muhmacro_for_cxt(COUNT, MACRO, SEP, CONTEXT) \
        muhmacro_concat(muhmacro_for_cxt, COUNT)(MACRO, SEP, CONTEXT)

/**
 * Returns the first argument given. At least one argument must be provided.
 *
 * This is useful when implementing a variadic macro, where you may have only
 * one variadic argument, but no way to retrieve it (for example, because \c ...
 * always needs to match at least one argument).
 *
 * @code

#define varmacro(...) \
    muhmacro_head(__VA_ARGS__)

 * @endcode
 */
#define muhmacro_head(...) \
        muhmacro_head_(__VA_ARGS__, 0)

/**
 * Returns every argument except the first. At least two arguments must be
 * provided.
 */
#define muhmacro_tail(...) \
        muhmacro_tail_(__VA_ARGS__)

/**
 * Returns the first N (up to twenty) variadic arguments as a new argument list.
 * At least N variadic arguments must be provided.
 */
#define muhmacro_take(N, ...) \
        muhmacro_concat(muhmacro_take, N)(__VA_ARGS__)

/**
 * Removes the first N (up to twenty) variadic arguments from the given argument
 * list. At least N variadic arguments must be provided.
 */
#define muhmacro_drop(N, ...) \
        muhmacro_concat(muhmacro_drop, N)(__VA_ARGS__)

/**
 * Decrements VAL, which must be a number between zero and twenty, inclusive.
 *
 * This is primarily useful when dealing with indexes and counts in
 * metaprogramming.
 */
#define muhmacro_dec(VAL) \
        muhmacro_at(VAL, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19)

/**
 * Increments VAL, which must be a number between zero and twenty, inclusive.
 *
 * This is primarily useful when dealing with indexes and counts in
 * metaprogramming.
 */
#define muhmacro_inc(VAL) \
        muhmacro_at(VAL, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21)

/**
 * If A is equal to B, the next argument list is expanded; otherwise, the
 * argument list after that is expanded. A and B must be numbers between zero
 * and twenty, inclusive. Additionally, B must be greater than or equal to A.
 *
 * @code

// expands to true
muhmacro_if_eq(0, 0)(true)(false)

// expands to false
muhmacro_if_eq(0, 1)(true)(false)

 * @endcode
 *
 * This is primarily useful when dealing with indexes and counts in
 * metaprogramming.
 */
#define muhmacro_if_eq(A, B) \
        muhmacro_concat(muhmacro_if_eq, A)(B)

/**
 * Identical to #muhmacro_if_eq. This can be used when the former would fail
 * due to recursive macro expansion.
 */
#define muhmacro_if_eq_recursive(A, B) \
        muhmacro_concat(muhmacro_if_eq_recursive, A)(B)

/**
 * Returns 1 if N is an even number, or 0 otherwise. N must be between zero and
 * twenty, inclusive.
 *
 * For the purposes of this test, zero is considered even.
 */
#define muhmacro_is_even(N) \
        muhmacro_at(N, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1)

/**
 * Returns the logical NOT of B, which must be the number zero or one.
 */
#define muhmacro_not(B) \
        muhmacro_at(B, 1, 0)

// IMPLEMENTATION DETAILS FOLLOW!
// Do not write code that depends on anything below this line.
#define muhmacro_stringify_(VALUE) # VALUE
#define muhmacro_concat_(A, B) A ## B
#define muhmacro_foreach_iter(INDEX, MACRO, ARG) MACRO(INDEX, ARG)
#define muhmacro_head_(FIRST, ...) FIRST
#define muhmacro_tail_(FIRST, ...) __VA_ARGS__
#define muhmacro_consume_(...)
#define muhmacro_expand_(...) __VA_ARGS__

// implemented from scratch so that muhmacro_concat() doesn't end up nesting
#define muhmacro_foreach_concat_iter(INDEX, BASE, ARG) muhmacro_foreach_concat_iter_(BASE, ARG)
#define muhmacro_foreach_concat_iter_(BASE, ARG) BASE ## ARG

// muhmacro_at expansions
#define muhmacro_at0(...) muhmacro_head(__VA_ARGS__)
#define muhmacro_at1(_0, ...) muhmacro_head(__VA_ARGS__)
#define muhmacro_at2(_0, _1, ...) muhmacro_head(__VA_ARGS__)
#define muhmacro_at3(_0, _1, _2, ...) muhmacro_head(__VA_ARGS__)
#define muhmacro_at4(_0, _1, _2, _3, ...) muhmacro_head(__VA_ARGS__)
#define muhmacro_at5(_0, _1, _2, _3, _4, ...) muhmacro_head(__VA_ARGS__)
#define muhmacro_at6(_0, _1, _2, _3, _4, _5, ...) muhmacro_head(__VA_ARGS__)
#define muhmacro_at7(_0, _1, _2, _3, _4, _5, _6, ...) muhmacro_head(__VA_ARGS__)
#define muhmacro_at8(_0, _1, _2, _3, _4, _5, _6, _7, ...) muhmacro_head(__VA_ARGS__)
#define muhmacro_at9(_0, _1, _2, _3, _4, _5, _6, _7, _8, ...) muhmacro_head(__VA_ARGS__)
#define muhmacro_at10(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, ...) muhmacro_head(__VA_ARGS__)
#define muhmacro_at11(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, ...) muhmacro_head(__VA_ARGS__)
#define muhmacro_at12(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, ...) muhmacro_head(__VA_ARGS__)
#define muhmacro_at13(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, ...) muhmacro_head(__VA_ARGS__)
#define muhmacro_at14(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, ...) muhmacro_head(__VA_ARGS__)
#define muhmacro_at15(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, ...) muhmacro_head(__VA_ARGS__)
#define muhmacro_at16(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, ...) muhmacro_head(__VA_ARGS__)
#define muhmacro_at17(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, ...) muhmacro_head(__VA_ARGS__)
#define muhmacro_at18(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, ...) muhmacro_head(__VA_ARGS__)
#define muhmacro_at19(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, ...) muhmacro_head(__VA_ARGS__)
#define muhmacro_at20(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, ...) muhmacro_head(__VA_ARGS__)

// muhmacro_foreach_cxt expansions
#define muhmacro_foreach_cxt0(MACRO, SEP, CONTEXT)
#define muhmacro_foreach_cxt1(MACRO, SEP, CONTEXT, _0) MACRO(0, CONTEXT, _0)

#define muhmacro_foreach_cxt2(MACRO, SEP, CONTEXT, _0, _1) \
    muhmacro_foreach_cxt1(MACRO, SEP, CONTEXT, _0) \
    SEP \
    MACRO(1, CONTEXT, _1)

#define muhmacro_foreach_cxt3(MACRO, SEP, CONTEXT, _0, _1, _2) \
    muhmacro_foreach_cxt2(MACRO, SEP, CONTEXT, _0, _1) \
    SEP \
    MACRO(2, CONTEXT, _2)

#define muhmacro_foreach_cxt4(MACRO, SEP, CONTEXT, _0, _1, _2, _3) \
    muhmacro_foreach_cxt3(MACRO, SEP, CONTEXT, _0, _1, _2) \
    SEP \
    MACRO(3, CONTEXT, _3)

#define muhmacro_foreach_cxt5(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4) \
    muhmacro_foreach_cxt4(MACRO, SEP, CONTEXT, _0, _1, _2, _3) \
    SEP \
    MACRO(4, CONTEXT, _4)

#define muhmacro_foreach_cxt6(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5) \
    muhmacro_foreach_cxt5(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4) \
    SEP \
    MACRO(5, CONTEXT, _5)

#define muhmacro_foreach_cxt7(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6) \
    muhmacro_foreach_cxt6(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5) \
    SEP \
    MACRO(6, CONTEXT, _6)

#define muhmacro_foreach_cxt8(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7) \
    muhmacro_foreach_cxt7(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6) \
    SEP \
    MACRO(7, CONTEXT, _7)

#define muhmacro_foreach_cxt9(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
    muhmacro_foreach_cxt8(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7) \
    SEP \
    MACRO(8, CONTEXT, _8)

#define muhmacro_foreach_cxt10(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
    muhmacro_foreach_cxt9(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
    SEP \
    MACRO(9, CONTEXT, _9)

#define muhmacro_foreach_cxt11(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
    muhmacro_foreach_cxt10(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
    SEP \
    MACRO(10, CONTEXT, _10)

#define muhmacro_foreach_cxt12(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
    muhmacro_foreach_cxt11(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
    SEP \
    MACRO(11, CONTEXT, _11)

#define muhmacro_foreach_cxt13(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
    muhmacro_foreach_cxt12(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
    SEP \
    MACRO(12, CONTEXT, _12)

#define muhmacro_foreach_cxt14(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
    muhmacro_foreach_cxt13(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
    SEP \
    MACRO(13, CONTEXT, _13)

#define muhmacro_foreach_cxt15(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
    muhmacro_foreach_cxt14(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
    SEP \
    MACRO(14, CONTEXT, _14)

#define muhmacro_foreach_cxt16(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
    muhmacro_foreach_cxt15(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
    SEP \
    MACRO(15, CONTEXT, _15)

#define muhmacro_foreach_cxt17(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
    muhmacro_foreach_cxt16(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
    SEP \
    MACRO(16, CONTEXT, _16)

#define muhmacro_foreach_cxt18(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
    muhmacro_foreach_cxt17(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
    SEP \
    MACRO(17, CONTEXT, _17)

#define muhmacro_foreach_cxt19(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
    muhmacro_foreach_cxt18(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
    SEP \
    MACRO(18, CONTEXT, _18)

#define muhmacro_foreach_cxt20(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) \
    muhmacro_foreach_cxt19(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
    SEP \
    MACRO(19, CONTEXT, _19)

// muhmacro_foreach_cxt_recursive expansions
#define muhmacro_foreach_cxt_recursive0(MACRO, SEP, CONTEXT)
#define muhmacro_foreach_cxt_recursive1(MACRO, SEP, CONTEXT, _0) MACRO(0, CONTEXT, _0)

#define muhmacro_foreach_cxt_recursive2(MACRO, SEP, CONTEXT, _0, _1) \
    muhmacro_foreach_cxt_recursive1(MACRO, SEP, CONTEXT, _0) \
    SEP \
    MACRO(1, CONTEXT, _1)

#define muhmacro_foreach_cxt_recursive3(MACRO, SEP, CONTEXT, _0, _1, _2) \
    muhmacro_foreach_cxt_recursive2(MACRO, SEP, CONTEXT, _0, _1) \
    SEP \
    MACRO(2, CONTEXT, _2)

#define muhmacro_foreach_cxt_recursive4(MACRO, SEP, CONTEXT, _0, _1, _2, _3) \
    muhmacro_foreach_cxt_recursive3(MACRO, SEP, CONTEXT, _0, _1, _2) \
    SEP \
    MACRO(3, CONTEXT, _3)

#define muhmacro_foreach_cxt_recursive5(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4) \
    muhmacro_foreach_cxt_recursive4(MACRO, SEP, CONTEXT, _0, _1, _2, _3) \
    SEP \
    MACRO(4, CONTEXT, _4)

#define muhmacro_foreach_cxt_recursive6(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5) \
    muhmacro_foreach_cxt_recursive5(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4) \
    SEP \
    MACRO(5, CONTEXT, _5)

#define muhmacro_foreach_cxt_recursive7(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6) \
    muhmacro_foreach_cxt_recursive6(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5) \
    SEP \
    MACRO(6, CONTEXT, _6)

#define muhmacro_foreach_cxt_recursive8(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7) \
    muhmacro_foreach_cxt_recursive7(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6) \
    SEP \
    MACRO(7, CONTEXT, _7)

#define muhmacro_foreach_cxt_recursive9(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
    muhmacro_foreach_cxt_recursive8(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7) \
    SEP \
    MACRO(8, CONTEXT, _8)

#define muhmacro_foreach_cxt_recursive10(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
    muhmacro_foreach_cxt_recursive9(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
    SEP \
    MACRO(9, CONTEXT, _9)

#define muhmacro_foreach_cxt_recursive11(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
    muhmacro_foreach_cxt_recursive10(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
    SEP \
    MACRO(10, CONTEXT, _10)

#define muhmacro_foreach_cxt_recursive12(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
    muhmacro_foreach_cxt_recursive11(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
    SEP \
    MACRO(11, CONTEXT, _11)

#define muhmacro_foreach_cxt_recursive13(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
    muhmacro_foreach_cxt_recursive12(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
    SEP \
    MACRO(12, CONTEXT, _12)

#define muhmacro_foreach_cxt_recursive14(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
    muhmacro_foreach_cxt_recursive13(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
    SEP \
    MACRO(13, CONTEXT, _13)

#define muhmacro_foreach_cxt_recursive15(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
    muhmacro_foreach_cxt_recursive14(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
    SEP \
    MACRO(14, CONTEXT, _14)

#define muhmacro_foreach_cxt_recursive16(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
    muhmacro_foreach_cxt_recursive15(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
    SEP \
    MACRO(15, CONTEXT, _15)

#define muhmacro_foreach_cxt_recursive17(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
    muhmacro_foreach_cxt_recursive16(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
    SEP \
    MACRO(16, CONTEXT, _16)

#define muhmacro_foreach_cxt_recursive18(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
    muhmacro_foreach_cxt_recursive17(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
    SEP \
    MACRO(17, CONTEXT, _17)

#define muhmacro_foreach_cxt_recursive19(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
    muhmacro_foreach_cxt_recursive18(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
    SEP \
    MACRO(18, CONTEXT, _18)

#define muhmacro_foreach_cxt_recursive20(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) \
    muhmacro_foreach_cxt_recursive19(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
    SEP \
    MACRO(19, CONTEXT, _19)

// muhmacro_for_cxt expansions
#define muhmacro_for_cxt0(MACRO, SEP, CONTEXT)
#define muhmacro_for_cxt1(MACRO, SEP, CONTEXT) MACRO(0, CONTEXT)

#define muhmacro_for_cxt2(MACRO, SEP, CONTEXT) \
    muhmacro_for_cxt1(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(1, CONTEXT)

#define muhmacro_for_cxt3(MACRO, SEP, CONTEXT) \
    muhmacro_for_cxt2(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(2, CONTEXT)

#define muhmacro_for_cxt4(MACRO, SEP, CONTEXT) \
    muhmacro_for_cxt3(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(3, CONTEXT)

#define muhmacro_for_cxt5(MACRO, SEP, CONTEXT) \
    muhmacro_for_cxt4(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(4, CONTEXT)

#define muhmacro_for_cxt6(MACRO, SEP, CONTEXT) \
    muhmacro_for_cxt5(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(5, CONTEXT)

#define muhmacro_for_cxt7(MACRO, SEP, CONTEXT) \
    muhmacro_for_cxt6(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(6, CONTEXT)

#define muhmacro_for_cxt8(MACRO, SEP, CONTEXT) \
    muhmacro_for_cxt7(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(7, CONTEXT)

#define muhmacro_for_cxt9(MACRO, SEP, CONTEXT) \
    muhmacro_for_cxt8(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(8, CONTEXT)

#define muhmacro_for_cxt10(MACRO, SEP, CONTEXT) \
    muhmacro_for_cxt9(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(9, CONTEXT)

#define muhmacro_for_cxt11(MACRO, SEP, CONTEXT) \
    muhmacro_for_cxt10(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(10, CONTEXT)

#define muhmacro_for_cxt12(MACRO, SEP, CONTEXT) \
    muhmacro_for_cxt11(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(11, CONTEXT)

#define muhmacro_for_cxt13(MACRO, SEP, CONTEXT) \
    muhmacro_for_cxt12(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(12, CONTEXT)

#define muhmacro_for_cxt14(MACRO, SEP, CONTEXT) \
    muhmacro_for_cxt13(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(13, CONTEXT)

#define muhmacro_for_cxt15(MACRO, SEP, CONTEXT) \
    muhmacro_for_cxt14(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(14, CONTEXT)

#define muhmacro_for_cxt16(MACRO, SEP, CONTEXT) \
    muhmacro_for_cxt15(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(15, CONTEXT)

#define muhmacro_for_cxt17(MACRO, SEP, CONTEXT) \
    muhmacro_for_cxt16(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(16, CONTEXT)

#define muhmacro_for_cxt18(MACRO, SEP, CONTEXT) \
    muhmacro_for_cxt17(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(17, CONTEXT)

#define muhmacro_for_cxt19(MACRO, SEP, CONTEXT) \
    muhmacro_for_cxt18(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(18, CONTEXT)

#define muhmacro_for_cxt20(MACRO, SEP, CONTEXT) \
    muhmacro_for_cxt19(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(19, CONTEXT)

// muhmacro_if_eq expansions
#define muhmacro_if_eq0(VALUE) \
    muhmacro_concat(muhmacro_if_eq0_, VALUE)

#define muhmacro_if_eq0_0(...) __VA_ARGS__ muhmacro_consume_
#define muhmacro_if_eq0_1(...) muhmacro_expand_
#define muhmacro_if_eq0_2(...) muhmacro_expand_
#define muhmacro_if_eq0_3(...) muhmacro_expand_
#define muhmacro_if_eq0_4(...) muhmacro_expand_
#define muhmacro_if_eq0_5(...) muhmacro_expand_
#define muhmacro_if_eq0_6(...) muhmacro_expand_
#define muhmacro_if_eq0_7(...) muhmacro_expand_
#define muhmacro_if_eq0_8(...) muhmacro_expand_
#define muhmacro_if_eq0_9(...) muhmacro_expand_
#define muhmacro_if_eq0_10(...) muhmacro_expand_
#define muhmacro_if_eq0_11(...) muhmacro_expand_
#define muhmacro_if_eq0_12(...) muhmacro_expand_
#define muhmacro_if_eq0_13(...) muhmacro_expand_
#define muhmacro_if_eq0_14(...) muhmacro_expand_
#define muhmacro_if_eq0_15(...) muhmacro_expand_
#define muhmacro_if_eq0_16(...) muhmacro_expand_
#define muhmacro_if_eq0_17(...) muhmacro_expand_
#define muhmacro_if_eq0_18(...) muhmacro_expand_
#define muhmacro_if_eq0_19(...) muhmacro_expand_
#define muhmacro_if_eq0_20(...) muhmacro_expand_

#define muhmacro_if_eq1(VALUE) muhmacro_if_eq0(muhmacro_dec(VALUE))
#define muhmacro_if_eq2(VALUE) muhmacro_if_eq1(muhmacro_dec(VALUE))
#define muhmacro_if_eq3(VALUE) muhmacro_if_eq2(muhmacro_dec(VALUE))
#define muhmacro_if_eq4(VALUE) muhmacro_if_eq3(muhmacro_dec(VALUE))
#define muhmacro_if_eq5(VALUE) muhmacro_if_eq4(muhmacro_dec(VALUE))
#define muhmacro_if_eq6(VALUE) muhmacro_if_eq5(muhmacro_dec(VALUE))
#define muhmacro_if_eq7(VALUE) muhmacro_if_eq6(muhmacro_dec(VALUE))
#define muhmacro_if_eq8(VALUE) muhmacro_if_eq7(muhmacro_dec(VALUE))
#define muhmacro_if_eq9(VALUE) muhmacro_if_eq8(muhmacro_dec(VALUE))
#define muhmacro_if_eq10(VALUE) muhmacro_if_eq9(muhmacro_dec(VALUE))
#define muhmacro_if_eq11(VALUE) muhmacro_if_eq10(muhmacro_dec(VALUE))
#define muhmacro_if_eq12(VALUE) muhmacro_if_eq11(muhmacro_dec(VALUE))
#define muhmacro_if_eq13(VALUE) muhmacro_if_eq12(muhmacro_dec(VALUE))
#define muhmacro_if_eq14(VALUE) muhmacro_if_eq13(muhmacro_dec(VALUE))
#define muhmacro_if_eq15(VALUE) muhmacro_if_eq14(muhmacro_dec(VALUE))
#define muhmacro_if_eq16(VALUE) muhmacro_if_eq15(muhmacro_dec(VALUE))
#define muhmacro_if_eq17(VALUE) muhmacro_if_eq16(muhmacro_dec(VALUE))
#define muhmacro_if_eq18(VALUE) muhmacro_if_eq17(muhmacro_dec(VALUE))
#define muhmacro_if_eq19(VALUE) muhmacro_if_eq18(muhmacro_dec(VALUE))
#define muhmacro_if_eq20(VALUE) muhmacro_if_eq19(muhmacro_dec(VALUE))

// muhmacro_if_eq_recursive expansions
#define muhmacro_if_eq_recursive0(VALUE) \
    muhmacro_concat(muhmacro_if_eq_recursive0_, VALUE)

#define muhmacro_if_eq_recursive0_0(...) __VA_ARGS__ muhmacro_consume_
#define muhmacro_if_eq_recursive0_1(...) muhmacro_expand_
#define muhmacro_if_eq_recursive0_2(...) muhmacro_expand_
#define muhmacro_if_eq_recursive0_3(...) muhmacro_expand_
#define muhmacro_if_eq_recursive0_4(...) muhmacro_expand_
#define muhmacro_if_eq_recursive0_5(...) muhmacro_expand_
#define muhmacro_if_eq_recursive0_6(...) muhmacro_expand_
#define muhmacro_if_eq_recursive0_7(...) muhmacro_expand_
#define muhmacro_if_eq_recursive0_8(...) muhmacro_expand_
#define muhmacro_if_eq_recursive0_9(...) muhmacro_expand_
#define muhmacro_if_eq_recursive0_10(...) muhmacro_expand_
#define muhmacro_if_eq_recursive0_11(...) muhmacro_expand_
#define muhmacro_if_eq_recursive0_12(...) muhmacro_expand_
#define muhmacro_if_eq_recursive0_13(...) muhmacro_expand_
#define muhmacro_if_eq_recursive0_14(...) muhmacro_expand_
#define muhmacro_if_eq_recursive0_15(...) muhmacro_expand_
#define muhmacro_if_eq_recursive0_16(...) muhmacro_expand_
#define muhmacro_if_eq_recursive0_17(...) muhmacro_expand_
#define muhmacro_if_eq_recursive0_18(...) muhmacro_expand_
#define muhmacro_if_eq_recursive0_19(...) muhmacro_expand_
#define muhmacro_if_eq_recursive0_20(...) muhmacro_expand_

#define muhmacro_if_eq_recursive1(VALUE) muhmacro_if_eq_recursive0(muhmacro_dec(VALUE))
#define muhmacro_if_eq_recursive2(VALUE) muhmacro_if_eq_recursive1(muhmacro_dec(VALUE))
#define muhmacro_if_eq_recursive3(VALUE) muhmacro_if_eq_recursive2(muhmacro_dec(VALUE))
#define muhmacro_if_eq_recursive4(VALUE) muhmacro_if_eq_recursive3(muhmacro_dec(VALUE))
#define muhmacro_if_eq_recursive5(VALUE) muhmacro_if_eq_recursive4(muhmacro_dec(VALUE))
#define muhmacro_if_eq_recursive6(VALUE) muhmacro_if_eq_recursive5(muhmacro_dec(VALUE))
#define muhmacro_if_eq_recursive7(VALUE) muhmacro_if_eq_recursive6(muhmacro_dec(VALUE))
#define muhmacro_if_eq_recursive8(VALUE) muhmacro_if_eq_recursive7(muhmacro_dec(VALUE))
#define muhmacro_if_eq_recursive9(VALUE) muhmacro_if_eq_recursive8(muhmacro_dec(VALUE))
#define muhmacro_if_eq_recursive10(VALUE) muhmacro_if_eq_recursive9(muhmacro_dec(VALUE))
#define muhmacro_if_eq_recursive11(VALUE) muhmacro_if_eq_recursive10(muhmacro_dec(VALUE))
#define muhmacro_if_eq_recursive12(VALUE) muhmacro_if_eq_recursive11(muhmacro_dec(VALUE))
#define muhmacro_if_eq_recursive13(VALUE) muhmacro_if_eq_recursive12(muhmacro_dec(VALUE))
#define muhmacro_if_eq_recursive14(VALUE) muhmacro_if_eq_recursive13(muhmacro_dec(VALUE))
#define muhmacro_if_eq_recursive15(VALUE) muhmacro_if_eq_recursive14(muhmacro_dec(VALUE))
#define muhmacro_if_eq_recursive16(VALUE) muhmacro_if_eq_recursive15(muhmacro_dec(VALUE))
#define muhmacro_if_eq_recursive17(VALUE) muhmacro_if_eq_recursive16(muhmacro_dec(VALUE))
#define muhmacro_if_eq_recursive18(VALUE) muhmacro_if_eq_recursive17(muhmacro_dec(VALUE))
#define muhmacro_if_eq_recursive19(VALUE) muhmacro_if_eq_recursive18(muhmacro_dec(VALUE))
#define muhmacro_if_eq_recursive20(VALUE) muhmacro_if_eq_recursive19(muhmacro_dec(VALUE))

// muhmacro_take expansions
#define muhmacro_take0(...)
#define muhmacro_take1(...) muhmacro_head(__VA_ARGS__)
#define muhmacro_take2(...) muhmacro_head(__VA_ARGS__), muhmacro_take1(muhmacro_tail(__VA_ARGS__))
#define muhmacro_take3(...) muhmacro_head(__VA_ARGS__), muhmacro_take2(muhmacro_tail(__VA_ARGS__))
#define muhmacro_take4(...) muhmacro_head(__VA_ARGS__), muhmacro_take3(muhmacro_tail(__VA_ARGS__))
#define muhmacro_take5(...) muhmacro_head(__VA_ARGS__), muhmacro_take4(muhmacro_tail(__VA_ARGS__))
#define muhmacro_take6(...) muhmacro_head(__VA_ARGS__), muhmacro_take5(muhmacro_tail(__VA_ARGS__))
#define muhmacro_take7(...) muhmacro_head(__VA_ARGS__), muhmacro_take6(muhmacro_tail(__VA_ARGS__))
#define muhmacro_take8(...) muhmacro_head(__VA_ARGS__), muhmacro_take7(muhmacro_tail(__VA_ARGS__))
#define muhmacro_take9(...) muhmacro_head(__VA_ARGS__), muhmacro_take8(muhmacro_tail(__VA_ARGS__))
#define muhmacro_take10(...) muhmacro_head(__VA_ARGS__), muhmacro_take9(muhmacro_tail(__VA_ARGS__))
#define muhmacro_take11(...) muhmacro_head(__VA_ARGS__), muhmacro_take10(muhmacro_tail(__VA_ARGS__))
#define muhmacro_take12(...) muhmacro_head(__VA_ARGS__), muhmacro_take11(muhmacro_tail(__VA_ARGS__))
#define muhmacro_take13(...) muhmacro_head(__VA_ARGS__), muhmacro_take12(muhmacro_tail(__VA_ARGS__))
#define muhmacro_take14(...) muhmacro_head(__VA_ARGS__), muhmacro_take13(muhmacro_tail(__VA_ARGS__))
#define muhmacro_take15(...) muhmacro_head(__VA_ARGS__), muhmacro_take14(muhmacro_tail(__VA_ARGS__))
#define muhmacro_take16(...) muhmacro_head(__VA_ARGS__), muhmacro_take15(muhmacro_tail(__VA_ARGS__))
#define muhmacro_take17(...) muhmacro_head(__VA_ARGS__), muhmacro_take16(muhmacro_tail(__VA_ARGS__))
#define muhmacro_take18(...) muhmacro_head(__VA_ARGS__), muhmacro_take17(muhmacro_tail(__VA_ARGS__))
#define muhmacro_take19(...) muhmacro_head(__VA_ARGS__), muhmacro_take18(muhmacro_tail(__VA_ARGS__))
#define muhmacro_take20(...) muhmacro_head(__VA_ARGS__), muhmacro_take19(muhmacro_tail(__VA_ARGS__))

// muhmacro_drop expansions
#define muhmacro_drop0(...) __VA_ARGS__
#define muhmacro_drop1(...) muhmacro_tail(__VA_ARGS__)
#define muhmacro_drop2(...) muhmacro_drop1(muhmacro_tail(__VA_ARGS__))
#define muhmacro_drop3(...) muhmacro_drop2(muhmacro_tail(__VA_ARGS__))
#define muhmacro_drop4(...) muhmacro_drop3(muhmacro_tail(__VA_ARGS__))
#define muhmacro_drop5(...) muhmacro_drop4(muhmacro_tail(__VA_ARGS__))
#define muhmacro_drop6(...) muhmacro_drop5(muhmacro_tail(__VA_ARGS__))
#define muhmacro_drop7(...) muhmacro_drop6(muhmacro_tail(__VA_ARGS__))
#define muhmacro_drop8(...) muhmacro_drop7(muhmacro_tail(__VA_ARGS__))
#define muhmacro_drop9(...) muhmacro_drop8(muhmacro_tail(__VA_ARGS__))
#define muhmacro_drop10(...) muhmacro_drop9(muhmacro_tail(__VA_ARGS__))
#define muhmacro_drop11(...) muhmacro_drop10(muhmacro_tail(__VA_ARGS__))
#define muhmacro_drop12(...) muhmacro_drop11(muhmacro_tail(__VA_ARGS__))
#define muhmacro_drop13(...) muhmacro_drop12(muhmacro_tail(__VA_ARGS__))
#define muhmacro_drop14(...) muhmacro_drop13(muhmacro_tail(__VA_ARGS__))
#define muhmacro_drop15(...) muhmacro_drop14(muhmacro_tail(__VA_ARGS__))
#define muhmacro_drop16(...) muhmacro_drop15(muhmacro_tail(__VA_ARGS__))
#define muhmacro_drop17(...) muhmacro_drop16(muhmacro_tail(__VA_ARGS__))
#define muhmacro_drop18(...) muhmacro_drop17(muhmacro_tail(__VA_ARGS__))
#define muhmacro_drop19(...) muhmacro_drop18(muhmacro_tail(__VA_ARGS__))
#define muhmacro_drop20(...) muhmacro_drop19(muhmacro_tail(__VA_ARGS__))
