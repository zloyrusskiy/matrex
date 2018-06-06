defmodule Matrex.Array.NIFs do
  @on_load :load_nifs

  @doc false
  @spec load_nifs :: :ok
  def load_nifs do
    priv_dir =
      case :code.priv_dir(__MODULE__) do
        {:error, _} ->
          ebin_dir = :code.which(__MODULE__) |> :filename.dirname()
          app_path = :filename.dirname(ebin_dir)
          :filename.join(app_path, "priv")

        path ->
          path
      end

    :ok = :erlang.load_nif(:filename.join(priv_dir, "array_nifs"), 0)
  end

  types = [
    "float64",
    "float32",
    "byte",
    "int16",
    "int32",
    "int64"
  ]

  Enum.each(types, fn type ->
    def unquote(:"add_arrays_#{type}")(data1, data2) when is_binary(data1) and is_binary(data2),
      do: :erlang.nif_error(:nif_library_not_loaded)

    def unquote(:"multiply_arrays_#{type}")(data1, data2)
        when is_binary(data1) and is_binary(data2),
        do: :erlang.nif_error(:nif_library_not_loaded)

    def unquote(:"array_sum_#{type}")(data) when is_binary(data),
      do: :erlang.nif_error(:nif_library_not_loaded)
  end)
end
