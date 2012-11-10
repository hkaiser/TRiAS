;;; $Id: Random_smob.scm,v 1.2 1999/05/16 00:14:18 trow Exp $

;;; 
;;; Random_smob.scm
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


(define %common-random (make-random))

;;
;; Some code to properly handle default arguments and access to a global,
;; "common" random object.
;;

(define (%random-frontend fn args default-args)
  (let* ((have-rnd (and (pair? args) (random? (car args))))
	 (our-obj (if have-rnd (car args) %common-random))
	 (our-args-1 (if have-rnd (cdr args) args))
	 (our-args (if (null? our-args-1) default-args our-args-1)))
    (apply fn (cons our-obj our-args))))

(define (random-integer! . rest)
  (%random-frontend %random-integer! rest '()))

(define (random-uniform! . rest)
  (%random-frontend %random-uniform! rest '(0 1)))

(define (random-normal! . rest)
  (%random-frontend %random-normal! rest '(0 1)))

(define (random-boolean! . rest)
  (%random-frontend %random-boolean! rest '(0.5)))

;;; $Id: Random_smob.scm,v 1.2 1999/05/16 00:14:18 trow Exp $