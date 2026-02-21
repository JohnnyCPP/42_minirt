/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_constants.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2025/12/17 02:49:28 by jonnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINIRT_CONSTANTS_H
# define MINIRT_CONSTANTS_H

# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define WIN_TITLE "miniRT"

// Key codes for Linux (X11)
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

# define EXIT_SUCCESS 0
# define EXIT_ERROR 1

// because computers can't represent decimal numbers with precission, 
// it's unsafe to write "x == 0.0" expression.
// To work around this, write an expression that evaluates under 
// a very small value "x < 1e-12".
//
// "1e-12" 
// - it's small enough to detect truly tiny vectors
// - it's large enough to avoid false positives from floating-point errors
// - it works well with typical scene scales (objects at distance 1-100 units)
//
// Think of it like measuring with a ruler:
// - if you measure something as 0 meters, it might actually be 0.0000001m
// - for practical purposes, that's still zero
// - "1e-12" is a way of saying "if it's this close to zero, treat it as zero"
//
// for shadow ray offset: quite lenient, for avoiding self-shadowing
# define EPSILON_SHADOW 1e-4
// for ray intersection tests: more lenient, for "close enough" in intersections
# define EPSILON_INTSEC 1e-6
// for checking if a vector is zero: very strict, for mathematical zero checks
//
// epsilon is the fifth letter of the Greek alphabet.
// In mathematics, it was introduced to represent 
// "an arbitrarily small quantity"
# define EPSILON 1e-12
// square of EPSILON for squared magnitude checks
# define EPSILON_SQ 1e-24

#endif
