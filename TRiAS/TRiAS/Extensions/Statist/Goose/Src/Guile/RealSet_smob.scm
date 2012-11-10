;;; $Id: RealSet_smob.scm,v 1.8 1999/07/09 19:51:51 trow Exp $

;;; 
;;; RealSet_smob.scm
;;;
;;; Copyright (C) 1999 EMC Capital Management
;;;
;;; Developed by Jon Trowbridge & Havoc Pennington
;;;
;;; This library is free software; you can redistribute it and/or
;;; modify it under the terms of the GNU Library General Public
;;; License as published by the Free Software Foundation; either
;;; version 2 of the License, or (at your option) any later version.
;;;
;;; This library is distributed in the hope that it will be useful,
;;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
;;; Library General Public License for more details.
;;;
;;; You should have received a copy of the GNU Library General Public
;;; License along with this library; if not, write to the Free Software
;;; Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
;;; 02111-1307, USA.
;;;

(define (realset-for-each fn rs)
  (define (iter i)
    (if (not (= i (realset-size rs)))
	(begin
	  (fn (realset-ref rs i))
	  (iter (1+ i)))))
  (iter 0))

(define (realset-map fn rs)
  (let ((new-rs (make-realset)))
    (define (iter i)
      (if (= i (realset-size rs))
	  new-rs
	  (begin
	    (realset-add! new-rs (fn (realset-ref rs i)))
	    (iter (1+ i)))))
    (iter 0)))

(define realset-add-one! realset-add!)

(define (realset->list x)
  (define (iter i acc)
    (if (negative? i) acc
	(iter (1- i) (cons (realset-ref x i) acc))))
  (iter (1- (realset-size x)) '()))

(define (realset-sorted->list x)
  (define (iter i acc)
    (if (negative? i) acc
	(iter (1- i) (cons (realset-sorted-ref x i) acc))))
  (iter (1- (realset-size x)) '()))


(define (list->realset l)
  (let ((rs (make-realset)))
    (for-each (lambda (x) (realset-add! rs x)) l)
    rs))

(define (realset->vector x)
  (let ((v (make-vector (realset-size x))))
    (define (iter i)
      (if (= i (realset-size x))
	  v
	  (begin
	    (vector-set! v i (realset-ref x i))
	    (iter (1+ i)))))
    (iter 0)))

(define (realset-sorted->vector x)
  (let ((v (make-vector (realset-size x))))
    (define (iter i)
      (if (= i (realset-size x))
	  v
	  (begin
	    (vector-set! v i (realset-sorted-ref x i))
	    (iter (1+ i)))))
    (iter 0)))


(define (vector->realset v)
  (let ((x (make-realset)))
    (define (iter i)
      (if (= i (vector-length v))
	  x
	  (begin
	    (realset-add! x (vector-ref v i))
	    (iter (1+ i)))))
    (iter 0)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (realset-not-equal-to rs x)
  (- (realset-size rs) (realset-equal-to rs x)))

(define (realset-greater-than-or-equal-to rs x)
  (+ (realset-greater-than rs x) (realset-equal-to rs x)))

(define (realset-less-than-or-equal-to rs x)
  (+ (realset-less-than rs x) (realset-equal-to rs x)))

(define (realset-%-greater-than rs x)
  (/ (realset-greater-than rs x) (realset-size rs)))

(define (realset-%-less-than rs x)
  (/ (realset-less-than rs x) (realset-size rs)))

(define (realset-%-between rs x y)
  (/ (realset-between rs x y) (realset-size rs)))

(define (realset-%-equal-to rs x)
  (/ (realset-equal-to rs x) (realset-size rs)))

(define (realset-%-greater-than-or-equal-to rs x)
  (/ (realset-greater-than-or-equal-to rs x) (realset-size rs)))

(define (realset-%-less-than-or-equal-to rs x)
  (/ (realset-less-than-or-equal-to rs x) (realset-size rs)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (realset-gmean-threshold-percentile rs c)
  (realset-%-greater-than rs (realset-gmean-threshold rs c)))
	    








;;; $Id: RealSet_smob.scm,v 1.8 1999/07/09 19:51:51 trow Exp $
