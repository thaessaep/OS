@set /p dir_name="Input name: "
@set new_dir=%cd%\%dir_name%
@mkdir %new_dir%

::~n - выделяет имя файла
@for %%f in (*.txt) do (
	@mkdir %new_dir%\%%~nf
	@copy %cd%\%%f %new_dir%\%%~nf
)
pause